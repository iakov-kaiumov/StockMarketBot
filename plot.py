import sys
import matplotlib.pyplot as plt
import matplotlib.dates as dates
import mpl_finance as mpf
import datetime
from peewee import *

# Const
STICKS = 10

db = SqliteDatabase('db.sqlite')


class BaseModel(Model):
    class Meta:
        database = db


class Price(BaseModel):
    dId = PrimaryKeyField()
    share = CharField()
    time = IntegerField()
    ask = DoubleField()
    bid = DoubleField()


def lines(since, shares, prices, path):
    # Current time
    now = datetime.datetime.now().timestamp()
    date_formatter = dates.DateFormatter("%d-%m")
    if now - since < 3600 * 24 * 7:
        date_formatter = dates.DateFormatter("%d-%m %H:%M")
    if now - since < 4000:
        date_formatter = dates.DateFormatter("%H:%M")
    # Create subplots
    fig, ax = plt.subplots(len(shares), figsize=(12, 10))

    index = 0
    for share in shares:
        x = []
        ask = []
        bid = []
        for p in prices[share]:
            x.append(dates.date2num(datetime.datetime.fromtimestamp(p.time)))
            ask.append(p.ask)
            bid.append(p.bid)
        # Draw current ask and bid
        ax[index].axhline(prices[share][-1].ask, linestyle='dashed', color='b', alpha=0.5)
        ax[index].axhline(prices[share][-1].bid, linestyle='dashed', color='r', alpha=0.5)
        # Set title
        ax[index].set_title('Share ' + share)
        ax[index].plot(x, ask, color='b', label='Ask')
        ax[index].plot(x, bid, color='r', label='Bid')
        ax[index].xaxis.set_major_formatter(date_formatter)

        index += 1

    plt.legend(loc='best')
    plt.savefig(path)


def candlesticks(since, shares, prices, path):
    # Current time
    now = datetime.datetime.now().timestamp()
    date_formatter = dates.DateFormatter("%d-%m")
    if now - since < 3600 * 24 * 7:
        date_formatter = dates.DateFormatter("%d-%m %H:%M")
    if now - since < 4000:
        date_formatter = dates.DateFormatter("%H:%M")

    # Create subplots
    fig, ax = plt.subplots(len(shares), figsize=(12, 10))

    index = 0
    for share in shares:
        x = []
        y = []
        quotes = []
        for p in prices[share]:
            x.append(p.time)
            y.append(p.ask)

        # Draw current ask and bid
        ax[index].axhline(prices[share][-1].ask, linestyle='dashed', color='b', label='Ask', alpha=0.5)
        ax[index].axhline(prices[share][-1].bid, linestyle='dashed', color='r', label='Bid', alpha=0.5)
        # Set title
        ax[index].set_title('Share ' + share)
        # Calculate step
        step = len(x) // STICKS
        if step > 1:
            for i in range(0, len(x), step):
                bound = i + step
                if i + step >= len(x):
                    break
                time = dates.date2num(datetime.datetime.fromtimestamp(x[i]))
                opn = y[i]
                close = y[bound - 1]
                high = max(y[i: bound])
                low = min(y[i: bound])
                if opn == close == high == low:
                    opn += 0.05
                    close -= 0.05
                quotes.append((time, opn, close, high, low))
            ax[index].set_title('Share ' + share)
            mpf.candlestick_ochl(ax[index], quotes, width=0.3 / STICKS * (quotes[-1][0] - quotes[0][0]), colorup='g', colordown='r')
            ax[index].xaxis.set_major_formatter(date_formatter)

            # fig.autofmt_xdate()
        index += 1

    plt.legend(loc='best')
    plt.savefig(path)


def main():
    # Load arguments
    style = sys.argv[1]
    since = int(sys.argv[2])
    shares = []
    for i in range(3, len(sys.argv)):
        shares.append(sys.argv[i])

    # Connect to the database
    db.connect()
    # Load prices
    prices = dict()
    for share in shares:
        p = list(Price.select().where(Price.share == share).where(Price.time > since).order_by(Price.time))
        if len(p) == 0:
            p = list(Price.select().where(Price.share == share).order_by(Price.time))[-1]
        prices[share] = p
    # Draw
    if style == 'L':
        lines(since, shares, prices, 'graphics/image.png')
    else:
        candlesticks(since, shares, prices, 'graphics/image.png')


if __name__ == '__main__':
    main()
