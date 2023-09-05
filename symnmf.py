import sys
import numpy as np
import symnmfssp
np.random.seed(0)

MAX_ITER = 300
EPS = 10 ** (-4)

"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ INPUT HANDLING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"


class GoalEnum:
    symnmf = 0
    sym = 1
    ddg = 2
    norm = 3

    @staticmethod
    def get_goal(g: str) -> int:
        if g == "symnmf":
            return GoalEnum.symnmf
        elif g == "sym":
            return GoalEnum.sym
        elif g == "ddg":
            return GoalEnum.ddg
        return GoalEnum.norm


def get_input():
    k, goal, file_path = sys.argv[1], sys.argv[2], sys.argv[3]
    vectors_list = file_to_vectors(file_path)
    try:
        k = int(k)
    except:
        print("Invalid number of clusters!")
    assert 1 < k < len(vectors_list), "Invalid number of clusters!"
    goal = GoalEnum.get_goal(goal)
    return k, goal, vectors_list


def file_to_vectors(file_path):
    with open(file_path, 'r') as file:
        vectors = []
        for line in file:
            vector = line.strip().split(",")
            vector = [float(x) for x in vector]
            vectors.append(vector)
    file.close()
    return vectors


def init_h(n, k, m):
    """
    :param n:   num of vecs
    :param k:   num of clusters
    :param m:   average of all entries of W
    :return:    H matrix
    """
    high = 2 * (m / k) ** 0.5
    return np.random.uniform(high=high, size=(n, k)).tolist()


def _calc_m(w):
    total_sum = 0
    count = 0
    for vector in w:
        for value in vector:
            total_sum += value
            count += 1
    return total_sum / count if count != 0 else 0


def print_vectors(centroids_list):
    for centroid in centroids_list:
        print(",".join([f"{x:.4f}" for x in centroid]))
    print()


def symnmf_main(analysis=False, k=3, goal=GoalEnum.symnmf, vectors_list=None):
    if not analysis:
        k, goal, vectors_list = get_input()
    if goal == GoalEnum.symnmf:
        w = symnmfssp.norm(vectors_list, len(vectors_list), len(vectors_list[0]))
        h = init_h(len(vectors_list), k, _calc_m(w))
        result = symnmfssp.symnmf(h, len(h), len(h[0]), w, len(w), len(w[0]), MAX_ITER, EPS)
    elif goal == GoalEnum.sym:
        result = symnmfssp.sym(vectors_list, len(vectors_list), len(vectors_list[0]))
    elif goal == GoalEnum.ddg:
        result = symnmfssp.ddg(vectors_list, len(vectors_list), len(vectors_list[0]))
    elif goal == GoalEnum.norm:
        result = symnmfssp.norm(vectors_list, len(vectors_list), len(vectors_list[0]))
    else:
        print("an error has occurred")
        raise Exception
    print_vectors(result)


if __name__ == '__main__':
    symnmf_main()
