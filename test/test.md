```
int length = MT.size();
    for (int i = 0; i < MT[0].size(); i++) {
        for (int j = 0; j <= length; j++) {
            if (MT[i][j].hash.empty()) {
                break;
            }
            cout << i << "," << j << " has hash " << MT[i][j].hash << "\n";
        }
        length /= 2;
    }
    