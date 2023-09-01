import math
import copy


def hw1_main(k, max_iter, vectors_list):
    centroids_list = kmeans(k, vectors_list, max_iter)
    return [round_vector(centroid) for centroid in centroids_list]


def parse_file(file_path):
    #convert file into list of vectors
    with open(file_path, 'r') as file:
        vectors = []
        for line in file:
            vector = line.strip().split(",")
            vector = [float(x) for x in vector]
            vectors.append(vector)
    return vectors


def round_vector(vector):
    return [format(round(x, 4), '.4f') for x in vector]


def kmeans(k: int, vectors_list: list, max_iter, eps=0.001):
    vectors_list_copy = copy.deepcopy(vectors_list)
    centroids = [(vectors_list_copy[i], []) for i in range(k)]
    iteration_number = 0
    max_miu_k = math.inf
    while (iteration_number < max_iter and max_miu_k >= eps):
        for x in vectors_list:
            closest_centroid = min(centroids, key=lambda centroid : euclidean_dis(x, centroid[0]))
            closest_centroid[1].append(x)
        delta = []
        for centroid in centroids:
            delta.append(update(centroid))
        max_miu_k = max(delta)
        iteration_number += 1
    return [centroid[0] for centroid in centroids]


def euclidean_dis(vec1: list, vec2: list) -> float:
    sum = 0
    for i in range(len(vec1)):
        sum += (vec1[i] - vec2[i])**2
    return math.sqrt(sum)


def update(centroid) -> float:
    vectors_list = [x.copy() for x in centroid[1]]
    curr_centroid = [x for x in centroid[0]]
    dimension = len(curr_centroid)
    vectors_list_size = len(vectors_list)
    for i in range(dimension):
        centroid[0][i] = (sum(vectors_list[j][i] for j in range(vectors_list_size))) / vectors_list_size
    centroid[1].clear()
    return euclidean_dis(curr_centroid, centroid[0])