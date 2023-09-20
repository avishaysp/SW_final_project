import math
import numpy as np
import pandas as pd
import sys
import mykmeanssp as kmeans

DEFAULT_MAX_ITER = 300



def main(bonus_run=False, k=1, vectors=None):
    k, max_iter, eps, vectors = get_input_bonus_wrap(bonus_run, k, vectors)
    centroids = init_centroids(vectors, k)

    list_of_centroids = get_python_list(centroids)
    list_of_vectors = get_python_list(vectors)
    result_centroids = kmeans.fit(k, max_iter, len(list_of_vectors), len(list_of_vectors[0]), eps, list_of_vectors, list_of_centroids)
    if not bonus_run:
        print_selected_indices(centroids)
        print_centroids(result_centroids)
        print()
    else:
        return result_centroids


def print_selected_indices(centeroids: pd.DataFrame):
    index_list = list(map(str, centeroids.index))
    print(",".join(index_list))


def print_centroids(centroids: list):
    for centroid in centroids:
        str_list = list(map(str, centroid))
        str_list = ["%.4f" % float(x) for x in str_list]
        print(",".join(str_list))


def get_input_bonus_wrap(bonus_run, k, vectors):
    if not bonus_run:
        k, max_iter, eps, vectors = get_input()
    else:
        max_iter, eps, vectors = 1000, 0.0, pd.DataFrame(vectors)
    return k, max_iter, eps, vectors


def get_input():
    if len(sys.argv) == 5:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], DEFAULT_MAX_ITER, sys.argv[2], sys.argv[3], sys.argv[4]
    else:
        k, max_iter, eps, file_path1, file_path2 = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]
    try:
        k = int(k)
    except Exception as e:
        print("Invalid number of clusters!")
        sys.exit(1)
    try:
        max_iter = int(max_iter)
    except Exception as e:
        print("Invalid maximum iteration!")
        sys.exit(1)
    try:
        eps = float(eps)
    except Exception as e:
        print("Invalid eps!")
        sys.exit(1)
    assert 1 < max_iter < 1000, "Invalid maximum iteration!"
    vectors1 = pd.read_csv(file_path1, header=None)
    vectors2 = pd.read_csv(file_path2, header=None)
    num_columns1 = len(vectors1.columns)
    num_columns2 = len(vectors2.columns)
    column_names1 = [f'column{i + 1}' for i in range(num_columns1)]
    column_names2 = [f'column{i + 1}' for i in range(num_columns2)]
    vectors1.columns = column_names1
    vectors2.columns = column_names2
    vectors = pd.merge(vectors1, vectors2, on="column1", how="inner")
    assert 1 < k < len(vectors), "Invalid number of clusters!"
    sorted_vectors = vectors.sort_values('column1', ascending=True)
    sorted_vectors.set_index('column1', inplace=True)
    sorted_vectors.index = sorted_vectors.index.astype(int)
    return k, max_iter, eps, sorted_vectors


def get_python_list(vectors: pd.DataFrame) -> list:
    return vectors.values.tolist()


def init_centroids(vectors: pd.DataFrame, k) -> pd.DataFrame:
    try:
        np.random.seed(0)
        rand_index = np.random.randint(0, len(vectors))
        centroids = pd.DataFrame(vectors.loc[rand_index]).T
        for i in range(k - 1):
            selected_centroid = select_vector(vectors.drop(centroids.index), centroids)
            centroids = pd.concat([centroids, selected_centroid.to_frame().T])
    except Exception as e:
        print("An Error Has Occurred")
        sys.exit(1)
    return centroids


def select_vector(vectors: pd.DataFrame, centroids: pd.DataFrame):
    diff = vectors - centroids.values[np.argmin(np.linalg.norm(vectors.values[:, None] - centroids.values, axis=2), axis=1)]
    dist_to_closest = np.sqrt((diff ** 2).sum(axis=1))
    sum_of_dist = np.sum(dist_to_closest)
    weights = dist_to_closest / sum_of_dist if sum_of_dist != 0 else np.full(len(vectors), 1 / len(vectors))
    selected_vector = np.random.choice(vectors.index, p=weights)
    return vectors.loc[selected_vector]


def calc_dist_to_closest(vector: pd.Series, centroids: pd.DataFrame) -> float:
    diff = centroids - vector
    dists = np.sqrt((diff**2).sum(axis=1))
    return dists.min()


def euclidean_dist(vector1: pd.Series, vector2: pd.Series) -> float:
    return np.sqrt(np.sum((vector1 - vector2)**2))


if __name__ == "__main__":
    main()
