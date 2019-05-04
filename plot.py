import matplotlib.pyplot as plt
import matplotlib.dates as dates


def main():
    # load args
    f = open('graphics/data.txt', 'r')
    lines = f.readlines()
    f.close()
    fig, ax = plt.subplots()
    for i in range(0, len(lines), 3):
        key = lines[i]
        x = lines[i+1].split()
        for j in range(len(x)):
            x[j] = dates.epoch2num(int(x[j]))
        y = list(map(float, lines[i+2].split()))
        ax.plot(x, y, label=key)

    date_formatter = dates.DateFormatter("%d-%m %H:%M")
    ax.xaxis.set_major_formatter(date_formatter)
    fig.autofmt_xdate()
    plt.legend(loc='best')
    plt.grid()
    plt.savefig('graphics/image.png')


if __name__ == '__main__':
    main()
