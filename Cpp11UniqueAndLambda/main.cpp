#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

using namespace std;

// Some data which we want to store
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

class BlobContainer
{
public:
    void add(std::unique_ptr<Blob>& newBlob)
    {
        // Simple copy is not allowed, move semantics needed.
        blobs.push_back(std::move(newBlob));
    }

    // Run lambda expression on each element
    void ForEach(std::function<void(const Blob&)> lambda ) const
    {
        for(const auto& blob : blobs)
        {
            lambda(*blob);
        }
    }

    auto begin()
    {
        return blobs.begin();
    }

    auto end()
    {
        return blobs.end();
    }

private:
    // Here we store our blobs
    std::vector<std::unique_ptr<Blob>> blobs;

};

// In order to display the results
std::ostream& operator<<(std::ostream& stream, const Blob& blob)
{
    stream << "Blob(" << blob.x << "," << blob.y << ")";
    return stream;
}

int main()
{
    // Need to have a blob container
    BlobContainer blobs;

    // Adding 2 blobs
    std::unique_ptr<Blob> newBlob = std::make_unique<Blob>(12,34);
    blobs.add(newBlob);
    newBlob = std::make_unique<Blob>(56,78);
    blobs.add(newBlob);

    // After the add() the newBlob weak_ptr became nullptr, since
    // the container took the ownership.
    cout << ( newBlob ? "newBlob still valid" : "newBlob invalid" ) << endl;

    cout << "Contents:" << endl;
    blobs.ForEach( [](const Blob& blob){ cout << blob << endl; } );

    cout << "The content with iterators and std::for_each :" << endl;
    std::for_each(
        blobs.begin(),
        blobs.end(),
        [](std::unique_ptr<Blob>& blob)
            { cout << *blob << endl; });
}
