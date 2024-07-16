def averageWaitingTime(customers):
    now, wait = 0, 0
    for customer in customers:
        arrival = customer[0]
        time = customer[1]
        if arrival < now:
            now += time
            wait += (now - arrival)
        else:
            now = arrival + time
            wait += time
    return wait/len(customers)