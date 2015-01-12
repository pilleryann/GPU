#ifndef TAB_TOOLS_H_
#define TAB_TOOLS_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TabTools
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	TabTools();
	virtual ~TabTools();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	static double reduction(double* tab, int n);

	static  void init(double* tab,int n,double a);

    private:

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
