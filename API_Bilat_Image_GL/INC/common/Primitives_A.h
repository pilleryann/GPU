#ifndef PRIMITIVES_A_H
#define PRIMITIVES_A_H

#include "envGLImage.h"
#include "PrimitiveVisitors_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE Primitives_A
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Primitives_A()
	    {
	    isNeedToDelete = false;
	    }

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~Primitives_A()
	    {
	    //Nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/
    public:
	virtual void accept(PrimitiveVisitors_I &visitor)=0;

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    public:

	bool isNeedToDelete;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
