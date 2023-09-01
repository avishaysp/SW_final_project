import numpy as np
from sklearn.metrics import silhouette_score
import sys
from hw1 import hw1_main
from symnmf import symnmf_main, GoalEnum

MAX_ITER = 300


def get_input():
    if len(sys.argv) == 3:
        k, max_iter, file_path = sys.argv[1], MAX_ITER, sys.argv[2]
    elif len(sys.argv) == 4:
        k, max_iter, file_path = sys.argv[1], sys.argv[2], sys.argv[3]
    else:
        raise Exception()
    vectors_list = parse_file(file_path)
    try:
        k = int(k)
    except:
        print("Invalid number of clusters!")
    assert 1 < k < len(vectors_list), "Invalid number of clusters!"
    try:
        max_iter = int(max_iter)
    except:
        print("Invalid maximum iteration!")
    assert 1 < max_iter < 1000, "Invalid maximum iteration!"
    return k, vectors_list, max_iter


def parse_file(file_path) -> list:
    with open(file_path, 'r') as file:
        vectors = []
        for line in file:
            vector = line.strip().split(",")
            vector = [float(x) for x in vector]
            vectors.append(vector)
    return vectors


def assign_to_nearest_centroid(sample, centroids):
    distances = np.linalg.norm(sample - centroids, axis=1)
    return np.argmin(distances)


def main():
    k, vectors_list, max_iter = get_input()

    this_centroids = symnmf_main(analysis=True, k=k, goal=GoalEnum.symnmf, vectors_list=vectors_list)
    print_silhouette(this_centroids, vectors_list)

    hw1_centroids = hw1_main(k, MAX_ITER, vectors_list)
    print_silhouette(hw1_centroids, vectors_list)


def print_silhouette(centroids, vectors_list):
    this_cluster_labels = [assign_to_nearest_centroid(v, centroids) for v in vectors_list]
    this_ss = silhouette_score(vectors_list, this_cluster_labels)
    print(f'nmf: {round(this_ss, 4)}')


if __name__ == '__main__':
    main()

