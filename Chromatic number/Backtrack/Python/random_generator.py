import glob
import random


def random_input(no_max_vertices):
    for filename in sorted(glob.glob('tests/test_*.in', recursive=True)):
        with open(filename, "w+") as of:
            random_no_vertices = random.randrange(3, no_max_vertices+1)
            random_no_edges = random.randrange(1, (random_no_vertices*(random_no_vertices-1))/2+1)

            of.write('%d\n' % random_no_vertices)
            of.write('%d\n' % random_no_edges)

            while random_no_edges:
                edge_1 = random.randrange(0, random_no_vertices)
                edge_2 = random.randrange(0, random_no_vertices)

                if edge_1 != edge_2:
                    of.write('%d\n%d\n' % (edge_1, edge_2))
                    random_no_edges -= 1
            of.close()
