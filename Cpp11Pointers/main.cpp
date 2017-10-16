#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Blob
{
public:
    Blob(int x, int y)
        : x(x), y(y)
    {
    }

public:
    int x,y;
};

void show(std::weak_ptr<Blob>& blob)
{
    std::shared_ptr<Blob> lockedBlob = blob.lock();
    if (lockedBlob) {
        cout << "Blob(" << lockedBlob->x << ","
             << lockedBlob->y << ")" << endl;
    } else {
        cout << "The Blob not exists." << endl;
    }
}

int main()
{
    // Create the two containers
    std::vector<std::shared_ptr<Blob>> container0;
    std::vector<std::shared_ptr<Blob>> container1;
    // Fill them
    std::shared_ptr<Blob> newBlob =
            std::make_shared<Blob>(12,34);
    container0.push_back(newBlob);
    container1.push_back(newBlob);
    newBlob = std::make_shared<Blob>(56,78);
    container0.push_back(newBlob);

    // storing weak_ptr for the blob which is located in both containers
    std::weak_ptr<Blob> selectedBlob = container1[0];

    // Clears and the examination of the selected blob
    show(selectedBlob); // Blob(12,34)
    container1.clear();
    show(selectedBlob); // Blob(12,34)
    container0.clear();
    show(selectedBlob); // Már nem létezik.

    cout << "End." << endl;
}
