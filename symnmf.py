import sys


class Goal_e:
    symnmf = 0
    sym = 1
    ddg = 2
    norm = 3

    @staticmethod
    def get_goal(g: str) -> int:
        if g == "symnmf":
            return Goal_e.symnmf
        elif g == "sym":
            return Goal_e.sym
        elif g == "ddg":
            return Goal_e.ddg
        return Goal_e.norm


def get_input():
    k, goal, file_path = sys.argv[1], sys.argv[2], sys.argv[3]
    vectors_list = file_to_vectors(file_path)
    try:
        k = int(k)
    except:
        print("Invalid number of clusters!")
    assert 1 < k < len(vectors_list), "Invalid number of clusters!"
    goal = Goal_e.get_goal(goal)
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
