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

#endif // BUFFER_H
