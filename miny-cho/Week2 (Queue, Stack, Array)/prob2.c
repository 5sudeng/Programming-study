double averageWaitingTime(int** customers, int customersSize, int* customersColSize) {
    int now = 0;
    double wait = 0;
    for (int i=0; i<customersSize; i++) {
        if (customers[i][0] < now) {
            now += customers[i][1];
            wait += (now - customers[i][0]);
        } else {
            now = customers[i][0] + customers[i][1];
            wait += customers[i][1];
        }
    }
    return wait/customersSize;
}