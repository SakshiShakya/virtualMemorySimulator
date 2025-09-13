#include <iostream>
#include <fstream>

using namespace std;

const int PAGE_SIZE = 256;
const int TLB_SIZE = 128;
const int NUM_PAGES = 256;
const int NUM_FRAMES = 256;

struct TLBEntry {
    int page ;
    int frame ;
    TLBEntry(){
        page=-1;
        frame=-1; 
    }
};

class VMSimulator {
    //TLB 
    TLBEntry tlb[TLB_SIZE];

    //Page Table
    int pageTable[NUM_PAGES];

    // Main Memory
    char physicalMemory[PAGE_SIZE][NUM_FRAMES];


    int tlbIndex = 0;
    int nextFreeFrame = 0;

    int totalAddresses = 0;
    int pageFaults = 0;
    int tlbHits = 0;

public:
    void run(const string& addressFile, const string& outputFile) {
       
        //Initially no pages are present in frames(main memory)
        for(int i=i;i<NUM_PAGES;i++){pageTable[i]=-1;}

        for (int i = 0; i < TLB_SIZE; ++i) {
         tlb[i] = TLBEntry();  
        }
        
        ifstream addressStream(addressFile);
        ofstream outputStream(outputFile);

        if (!addressStream || !outputStream) {
            cerr << "Error opening files!" << endl;
            exit(1);
        }

        outputStream << "Logical Address,Physical Address\n";

        int logicalAddress;
        while (addressStream >> logicalAddress) {
            totalAddresses++;

            logicalAddress &= 0xFFFF;
            int pageNumber = (logicalAddress >> 8) & 0xFF;
            int offset = logicalAddress & 0xFF;

            int frameNumber = getFrameFromTLB(pageNumber);

            if (frameNumber != -1) {
                tlbHits++;
            } else if (pageTable[pageNumber] != -1) {
                frameNumber = pageTable[pageNumber];
                addToTLB(pageNumber, frameNumber);
            } else {
                pageFaults++;
                frameNumber = handlePageFault(pageNumber);
            }

            int physicalAddress = frameNumber * PAGE_SIZE + offset;

            outputStream << logicalAddress << "," << physicalAddress << "\n";
        }

        double pageFaultRate = (double)pageFaults / totalAddresses * 100.0;
        double tlbHitRate = (double)tlbHits / totalAddresses * 100.0;

       
        outputStream << "\nPage Fault Rate: " << pageFaultRate << "%\n";
        outputStream << "TLB Hit Rate: " << tlbHitRate << "%\n";

        cout << "Simulation Complete.\n";
        cout << "Total Addresses Translated: " << totalAddresses << "\n";
        cout << "Page Faults: " << pageFaults << "\n";
        cout << "TLB Hits: " << tlbHits << "\n";
        cout << "Page Fault Rate: " << pageFaultRate << "%\n";
        cout << "TLB Hit Rate: " << tlbHitRate << "%\n";
    }

private:
    int getFrameFromTLB(int pageNumber) {
        for (const auto& entry : tlb) {
            if (entry.page == pageNumber) {
                return entry.frame;
            }
        }
        return -1;
    }

    void addToTLB(int pageNumber, int frameNumber) {
        tlb[tlbIndex % TLB_SIZE].page = pageNumber;
        tlb[tlbIndex % TLB_SIZE].frame =  frameNumber;
        tlbIndex++;
    }

    int handlePageFault(int pageNumber) {
        if (nextFreeFrame >= NUM_FRAMES) {
            cerr << "Error: No free frames available.\n";
            exit(1);
        }

        // Simulate the content of the page: fill with value = page number
        for (int i = 0; i < PAGE_SIZE; ++i) {
            physicalMemory[nextFreeFrame][i] = (char)pageNumber;
        }

        pageTable[pageNumber] = nextFreeFrame;
        addToTLB(pageNumber, nextFreeFrame);
    
        return nextFreeFrame++;
    }
};

int main() {
    VMSimulator simulator;
    simulator.run("addresses.txt", "output.csv");
    return 0;
}
