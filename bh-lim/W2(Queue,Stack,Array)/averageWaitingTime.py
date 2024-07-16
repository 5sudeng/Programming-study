from typing import List

def averageWaitingTime(customers: List[List[int]]) -> float:
    ntime = customers[0][0]
    wtime = []
    wtime.append(customers[0][1])
    ntime = ntime + customers[0][1]
    for customer in customers[1:]:
        if customer[0] < ntime:
            wtime.append((ntime - customer[0]) + customer[1])
            ntime += customer[1]
        else:
            wtime.append(customer[1])
            ntime = customer[0] + customer[1]

    return sum(wtime)/len(wtime)

customers = [[5,2],[5,4],[10,3],[20,1]]
print(f"{averageWaitingTime(customers)}")