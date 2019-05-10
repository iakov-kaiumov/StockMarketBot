import sys
import matplotlib.pyplot as plt
import matplotlib.dates as dates
import datetime
from peewee import *

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


def main():
    fig, ax = plt.subplots()
    since = sys.argv[1]
    shares = []
    for i in range(2, len(sys.argv)):
        shares.append(sys.argv[i])

    db.connect()
    for share in shares:
        prices = list(Price.select().where(Price.share == share).where(Price.time > since).order_by(Price.time))
        x = []
        y = []
        for p in prices:
            x.append(datetime.datetime.fromtimestamp(p.time))
            y.append(p.ask)
        ax.plot(x, y, label=share)

    date_formatter = dates.DateFormatter("%d-%m %H:%M")
    ax.xaxis.set_major_formatter(date_formatter)
    fig.autofmt_xdate()
    plt.legend(loc='best')
    plt.grid()
    plt.savefig('graphics/image.png')


if __name__ == '__main__':
    main()
