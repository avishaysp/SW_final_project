import sys
import numpy as np
np.random.seed(0)

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
    print(k, goal, vectors_list, sep='\n\n')
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


def init_H(n, k, m):
    """
    :param n:   num of vecs
    :param k:   num of clusters
    :param m:   average of all entries of W
    :return:    H matrix
    """
    high = 2 * (m / k) ** 2
    print(high)
    return np.random.uniform(high=high, size=(n, k))


if __name__ == '__main__':
    k, goal, vectors_list = get_input()
    if goal == GoalEnum.symnmf:
        pass
    elif goal == GoalEnum.sym:
        pass
    elif goal == GoalEnum.ddg:
        pass
    elif goal == GoalEnum.norm:
        pass

# print(init_H(10, 3, 4))
