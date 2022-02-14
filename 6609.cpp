#include <iostream>
#include <stdlib.h>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;
void FIFO(int pages[], int length, int number_of_frames) {
    int pageFaults = 0;
    deque  <int> frames;
    vector <int> iframes{};
    unordered_set<int> indexes;

    cout << "Replacement Policy = FIFO\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
    for (int i = 0; i < length; ++i) {
        bool faulted = false;
        if(indexes.find(pages[i]) == indexes.end()){
            if(frames.size() == number_of_frames) {
                indexes.erase(frames.front());
                auto it = find(iframes.begin(), iframes.end(), frames.front());
                *it  = pages[i];
                frames.pop_front();
                pageFaults++;
                faulted = true;
            } else {
                iframes.push_back(pages[i]);
            }
            frames.push_back(pages[i]);
            indexes.insert(pages[i]);
        }
        printf("%02d %c   ",pages[i], faulted ? 'F':' ');
        for(auto& f:iframes){
            printf("%02d ",f);
        }
        putc('\n',stdout);
    }
    cout<<"-------------------------------------";
    cout << "\nNumber of page faults = " << pageFaults << endl;
}

void LRU(int pages[], int length, int number_of_frames) {
    int pageFaults = 0, m;
    int temp[number_of_frames], used[number_of_frames];
    for (m = 0; m < number_of_frames; m++)
    {
        temp[m] = -1;
        used[m] = 0;
    }
    cout << "Replacement Policy = LRU\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
    for (int i = 0; i < length; ++i)
    {    bool faulted = false;
        //if (pages[i] < 10) cout << "0";
        // cout << pages[i] << "        ";
        int flag = 0;
        for (int j = 0; j < number_of_frames; j++)
        {
            if (pages[i] == temp[j]) { //it will check whether the page already exist in frames or not
                flag = 1;
                used[j] = i + 1;
            }
        }
        if (flag == 0)
        {
            int min = 0;
            for (int k = 0; k < number_of_frames - 1; k++)
            {
                if (used[min] > used[k + 1]) //It will calculate the page which is least recently used
                    min = k + 1;
            }
            temp[min] = pages[i];
            used[min] = i + 1; //Increasing the time
            pageFaults++; //it will count the total Page Faults
            if(pageFaults > number_of_frames)
                faulted = true;
        }
        printf("%02d %c   ",pages[i], faulted ? 'F':' ');
        for(auto& f:temp){
            if(f == -1)
                continue;
            printf("%02d ",f);
        }
        putc('\n',stdout);
    }
    pageFaults -= number_of_frames;
    cout<<"-------------------------------------";
    cout << "\nNumber of page faults = " << pageFaults << endl;
}
typedef struct {
    int number;
    int used; //to specify if its used or not
}
        Clock_frame;
void CLOCK(int pages[], int length, int number_of_frames) {
    int pageFaults = 0, found, index = 0;
    Clock_frame temp[number_of_frames];
    for (int m = 0; m < number_of_frames; m++)
    {
        temp[m].number = -1;
        temp[m].used = 0;
    }
    cout << "Replacement Policy = CLOCK\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
    for (int i = 0; i < length; ++i) {
        bool faulted = false;
        //  if (pages[i] < 10) cout << "0";
        //  cout << pages[i] << "        ";
        found = 0;
        for (int j = 0; j < number_of_frames; ++j) {
            if (pages[i] == temp[j].number) {
                found = 1;
                temp[j].used = 1;
            }
        }
        if (found == 0) {
            do {
                if (temp[index].used == 0) {
                    temp[index].number = pages[i];
                    temp[index].used = 1;
                    found = 1;
                    pageFaults++;
                    if(pageFaults > number_of_frames)
                        faulted = true;
                } else {
                    temp[index].used = 0;
                }
                index++;
                if (index == number_of_frames) {
                    index = 0;
                }
            } while (found != 1);
        }
        printf("%02d %c   ",pages[i], faulted ? 'F':' ');
        for(auto& f:temp){
            if(f.number== -1)
                continue;
            printf("%02d ",f.number);
        }
        putc('\n',stdout);
    }
    pageFaults -= number_of_frames;
    cout<<"-------------------------------------";
    cout << "\nNumber of page faults = " << pageFaults << endl;
}

void Optimal(int pages[], int length, int number_of_frames) {
    int pageFaults = 0;
    vector<int> frames;
    unordered_set<int> indexes;

    cout << "Replacement Policy = OPTIMAL\n";
    cout << "-------------------------------------\n";
    cout << "Page   Content of Frames\n";
    cout << "----   -----------------\n";
    for (int i = 0; i < length; ++i) {
        bool faulted = false;
        if(indexes.find(pages[i]) == indexes.end()){
            if(frames.size() == number_of_frames) {
                int furthest = i + 1;
                int frame_to_eliminate = 0;
                for(int j=0;j < number_of_frames;j++){
                    for (int k= i + 1 ; k < length ; k++){
                        if(frames.at(j) == pages[k]){
                            if(k > furthest){
                                furthest = k;
                                frame_to_eliminate = j;
                            }
                            break;
                        }

                        if(k == length - 1){
                            frame_to_eliminate=j;
                            j = number_of_frames;
                        }
                    }
                }
                indexes.erase(frames.at(frame_to_eliminate));
                frames.at(frame_to_eliminate) = pages[i];
                pageFaults++;
                faulted = true;
            } else {
                frames.push_back(pages[i]);
            }
            indexes.insert(pages[i]);
        }

        printf("%02d %c   ",pages[i], faulted ? 'F':' ');

        for(auto& f:frames){
            printf("%02d ",f);
        }
        putc('\n',stdout);
    }
    cout<<"-------------------------------------";
    cout << "\nNumber of page faults = " << pageFaults << endl;
}
string replacement_policy;
int main() {
    int number_of_frames, length = 0;
    cin >> number_of_frames;
    cin >> replacement_policy;
    int * pages;
    pages = (int*) malloc(10000*sizeof(int));
    for (int i = 0; i < 10000; ++i) {
        cin >> pages[i];
        if (pages[i] != -1) length++;
        if (pages[i] == -1) break;
    }

    if (replacement_policy == "FIFO") {
        FIFO(pages, length, number_of_frames);
    } else if (replacement_policy == "LRU") {
        LRU(pages, length, number_of_frames);
    } else if (replacement_policy == "CLOCK") {
        CLOCK(pages, length, number_of_frames);
    } else if (replacement_policy == "OPTIMAL") {
        Optimal(pages, length, number_of_frames);
    }
    return 0;
}
