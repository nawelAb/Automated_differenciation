#include "values.h"

namespace ourlibs{
	
	//constructeur
	values::values(double a ,int b , int p)
	{
	m_v=a;
	m_size=b;
	m_tabdiv= new double [b];
	for (int i=0; i<b; i++)
		{
			if(i == p)
			{ 
				m_tabdiv[i]=1; 
			}
			else
			{
				m_tabdiv[i]=0;
			}
		}
	}

	values::values(double a ,int b)
	{
	m_v=a;
	m_size=b;
	m_tabdiv= new double [b];
	for (int i=0; i<b; i++)
		{
			m_tabdiv[i]=0;
		}
	}

    //distructeur
    values::~values()
	{
		delete[] m_tabdiv;
	}
	
	//accesseur
	double values::getvalue()
	{
		return m_v;
	}
	
	const int values::gettaille()
	{
		return m_size;
		
	}
	
	double values::gettabdiv( int i)
	{
		return m_tabdiv[i];
	}

	//operateur 
    values values::operator*(double a)
    {
    	values tmp( m_v, m_size) ;
    	tmp.m_v = m_v * a;

    	for (int i = 0; i < m_size; ++i)
    	{
    		tmp.m_tabdiv[i] = a*m_tabdiv[i];
    	}
    	return tmp;
    }

	 

	values operator+(double a)
		{
				values tmp( m_v, m_size, p) ;
		    	tmp.m_v = m_v + a;
		    	return tmp;
		}
	
	values operator+( ourlibs::values* v)
	{
		values tmp(m_v, m_size, p) ;
		tmp.m_v = m_v + v.getvalue() ;
		for (int i = 0; i < v.gettaille(); ++i)
    	{
    		tmp.m_tabdiv[i] = m_tabdiv[i] + v.gettabdiv(i);
    	}
    	return tmp;

	}


   values operator*(double a, ourlibs::values v)
    {
    	values tmp( v.getvalue(), v.gettaille() ) ;
    	tmp.m_v = v.getvalue() * a;

    	for (int i = 0; i < v.gettaille(); ++i)
    	{
    		tmp.m_tabdiv[i] = a*v.gettabdiv(i);
    	}
    	return tmp;
    }
}