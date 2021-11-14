#ifndef ISTENCILGENERATOR_H
#define ISTENCILGENERATOR_H

/**
 * Kenzie Evans
 * William Erignac
 * 11/10/2021
 *
 * @brief The IStencilGenerator class generates stencils for tools to use.
 */
class IStencilGenerator
{
public:
	/**
	 * @brief Fills the stencil parameter with weights representing this generator's shape.
	 * @param size The size of the stencil to fill.
	 */
	virtual void generate(int size, float** stencil) = 0;
};

#endif // ISTENCILGENERATOR_H
