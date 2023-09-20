import numpy as np
from sklearn.metrics import silhouette_score
import sys
from hw1 import hw1_main
from symnmf import symnmf_main, GoalEnum

MAX_ITER = 300
EPS = 10 ** (-4)
K = 6


def get_input():
    if len(sys.argv) == 2:
        file_path = sys.argv[1]
    else:
        print("An Error Has Occurred")
        exit()
    vectors_list = parse_file(file_path)
    return K, vectors_list, MAX_ITER


def parse_file(file_path) -> list:
    with open(file_path, 'r') as file:
        vectors = []
        for line in file:
            vector = line.strip().split(",")
            vector = [float(x) for x in vector]
            vectors.append(vector)
    return vectors


def main():
    k, vectors_list, max_iter = get_input()
    np_vectors_list = np.array(vectors_list)
    symnmf = symnmf_main(analysis=True, k=k, goal=GoalEnum.symnmf, vectors_list=vectors_list)
    print_silhouette_nmf(symnmf, np_vectors_list)

    hw1_centroids = hw1_main(k, MAX_ITER, vectors_list)
    np_hw1_centroids = np.array(hw1_centroids)
    print_silhouette_kmeans(np_hw1_centroids, np_vectors_list)


def print_silhouette_nmf(nmf, vectors_list):
    labels = get_highest_value_indices(nmf)
    this_ss = silhouette_score(vectors_list, labels)
    print(f'nmf: {this_ss:.4f}')

def print_silhouette_kmeans(centroids, vectors_list):
    labels = np.array([assign_to_nearest_centroid(v, centroids) for v in vectors_list])
    this_ss = silhouette_score(vectors_list, labels)
    print(f'kmeans: {this_ss:.4f}')


def assign_to_nearest_centroid(sample, centroids):
    distances = np.linalg.norm(sample - centroids, axis=1)
    return np.argmin(distances)


def get_highest_value_indices(vectors):
    return np.argmax(vectors, axis=1)


if __name__ == '__main__':
    main()

