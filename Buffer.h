#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:
  Buffer(int size);
  ~Buffer();

  void add(int value);
  int get(int index) const;

private:
  int *data;
  int size;
  int currentIndex;
};

Buffer::Buffer(int size) : size(size), currentIndex(0)
{
  data = new int[size];
}

Buffer::~Buffer() { delete[] data; }

void Buffer::add(int value)
{
  for (int i = size - 2; i >= 0; --i)
    data[i + 1] = data[i]; // Shift elements to the right

  data[0] = value; // Add new value at the start
}

int Buffer::get(int index) const
{
  if (index < 0 || index >= size)
    throw("Index out of range");

  return data[index];
}

#endif // BUFFER_H
