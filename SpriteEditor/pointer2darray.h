#ifndef POINTER2DARRAY_H
#define POINTER2DARRAY_H


template<typename T>
class Pointer2DArray
{
private:
	unsigned int width;
	unsigned int height;
	T **array;
public:
	Pointer2DArray(unsigned int width, unsigned int height);
	Pointer2DArray(const Pointer2DArray<T> &other);
	Pointer2DArray<T> &operator=(Pointer2DArray<T> otherCopy);
	~Pointer2DArray();

	T *operator[](unsigned int index) const;
	unsigned int getWidth() const ;
	unsigned int getHeight() const;
};

#endif // POINTER2DARRAY_H
