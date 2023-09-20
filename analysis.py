import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import silhouette_score
import sys
from hw1 import hw1_main
from symnmf import symnmf_main, GoalEnum

MAX_ITER = 300
EPS = 10 ** (-4)
K = 5


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
    plot_clusters(labels, vectors_list, "nmf")
    print(f'nmf: {round(this_ss, 16)}')


def print_silhouette_kmeans(centroids, vectors_list):
    labels = np.array([assign_to_nearest_centroid(v, centroids) for v in vectors_list])
    this_ss = silhouette_score(vectors_list, labels)
    plot_clusters(labels, vectors_list, "kmeans")
    print(f'kmeans: {round(this_ss, 16)}')


def assign_to_nearest_centroid(sample, centroids):
    distances = np.linalg.norm(sample - centroids, axis=1)
    return np.argmin(distances)


def get_highest_value_indices(vectors):
    return np.argmax(vectors, axis=1)


def plot_clusters(labels, vectors_list, title):
    tab1 = pd.DataFrame(vectors_list)
    tab1['columns'] = labels

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    x = np.array(tab1[0])
    y = np.array(tab1[1])
    z = np.array(tab1[2])

    ax.scatter(x, y, z, marker="o", c=tab1["columns"], s=1, cmap="viridis")

    ax.set_xlim(tab1[0].min() - 1, tab1[0].max() + 1)  # Replace x_min and x_max with your desired limits
    ax.set_ylim(tab1[1].min() - 1, tab1[1].max() + 1)  # Replace y_min and y_max with your desired limits
    ax.set_zlim(tab1[2].min() - 1, tab1[2].max() + 1)
    plt.title(title)
    plt.show()


if __name__ == '__main__':
    main()

