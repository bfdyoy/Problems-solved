import glob
import random


def random_input(no_max_towers):
    for filename in sorted(glob.glob('tests/test_*.in', recursive=True)):
        with open(filename, "w+") as of:

            random_no_towers = random.randrange(2, no_max_towers)
            random_no_tunnels = random.randrange(1, (random_no_towers * (random_no_towers+1)/2), 1)

            of.write('%d\n' % random_no_towers)
            of.write('%d\n' % random_no_tunnels)

            while random_no_tunnels:
                tower_1 = random.randrange(0, random_no_towers, 1)
                tower_2 = random.randrange(0, random_no_towers, 1)

                if tower_1 != tower_2:
                    of.write('%d\n%d\n' % (tower_1, tower_2))
                    random_no_tunnels -= 1

            of.close()
