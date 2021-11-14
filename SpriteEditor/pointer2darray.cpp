#include "pointer2darray.h"
#include <stdlib.h>
#include <algorithm>

/** Kenzie Evans
 *  William Erignac
 *  11/13/2021
 *
 *  @brief Pointer2DArray is a class acts like a 2D array, but that
 *  can be dynamically allocated (you don't need to know the width
 *  / height adhead of time).
 */

template<typename T>
/**
 * @brief Creates a 2D array full of junk (whatever's in memory).
 * @param width The width of the 2D array.
 * @param height the height of the 2D array.
 */
Pointer2DArray<T>::Pointer2DArray(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	array = (T**)malloc(width * sizeof(T*));

	for (int i = 0; i < width; i++)
		array[i] = (T*)malloc(height * sizeof(T));
}

template<typename T>
/**
 * @brief Creates a deep copy of another 2D array.
 */
Pointer2DArray<T>::Pointer2DArray(const Pointer2DArray<T>& other)
{
	width = other.width;
	height = other.height;

	array = (T**)malloc(width * sizeof(T*));

	for (int i = 0; i < width; i++)
	{
		array[i] = (T*) malloc(height * sizeof(T));
		for (int j = 0; j < height; j++)
			array[i][j] = other[i][j];
	}
}

template<typename T>
/**
 * @brief Creates a deep copy of another 2D array.
 */
Pointer2DArray<T>& Pointer2DArray<T>::operator=(Pointer2DArray<T> otherCopy)
{
	width = otherCopy.width;
	height = otherCopy.height;
	swap(array, otherCopy.array);
}

template<typename T>
/**
 * @brief Destroys this object's pointer array.
 */
Pointer2DArray<T>::~Pointer2DArray()
{
	for (int i = 0; i < width; i++)
		free(array[i]);
	free(array);
}


template<typename T>
/**
 * @brief Gets the column (from 0 to width) of the given index.
 * @param index index of the column to get.
 * @return pointer of Ts from 0 to height.
 */
T* const Pointer2DArray<T>::operator[](unsigned int index)
{
	return array[index];
}

template<typename T>
/**
 * @brief Gets the width of this 2D array.
 * @return the width.
 */
unsigned int const Pointer2DArray<T>::getWidth()
{
	return width;
}

template<typename T>
/**
 * @brief Gets the height of this 2D array.
 * @return the height.
 */
unsigned int const Pointer2DArray<T>::getHeight()
{
	return height;
}
