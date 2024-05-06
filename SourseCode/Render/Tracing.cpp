#include "Tracing.h"




Tracing::Tracing(const unsigned int& pointnum)
	:pointnum(pointnum),endpoint(0), pointnum_count_total(0)
{

	this->pointposse = new Vector3[this->pointnum]{};


}



Tracing::~Tracing()
{

	delete[] this->pointposse;


}



void Tracing::Draw()
{


		if (this->pointnum_count_total > this->pointnum)
		{
			for (unsigned int i = this->endpoint + 1; i < this->pointnum - 2; ++i)
			{
				DrawLine3D(this->pointposse[i], this->pointposse[i + 1], Trace_Color);
			}

			DrawLine3D(this->pointposse[this->pointnum - 1], this->pointposse[0], Trace_Color);

			if (this->endpoint != 0)
			{
				for (unsigned int j = 0; j < this->endpoint - 1; ++j)
				{

					DrawLine3D(this->pointposse[j], this->pointposse[j + 1], Trace_Color);

				}
			}
		}
		else if(this->pointnum_count_total >= 2)
		{

			for (unsigned int i = 0; i < this->pointnum_count_total - 2; ++i)
			{
				
				DrawLine3D(this->pointposse[i], this->pointposse[i + 1], Trace_Color);
			}


		}
		
	
	


}


void Tracing::pushTrace_exceptSame(const Vector3& pointpos)
{
	
	if(this->pointnum_count_total == 0)
	{


		this->pointposse[this->endpoint] = Vector3Scale(pointpos, COORD_ZOOM);

		++this->pointnum_count_total;


		return;
	}	


	if (Vector3Equals(Vector3Scale(pointpos, COORD_ZOOM), this->pointposse[this->endpoint]) == false)
	{
		if (this->endpoint != this->pointnum - 1)
		{
			this->pointposse[++this->endpoint] = Vector3Scale(pointpos, COORD_ZOOM);
		}
		else
		{
			this->endpoint = 0;
			this->pointposse[this->endpoint] = Vector3Scale(pointpos, COORD_ZOOM);

		}

		++this->pointnum_count_total;


	}



}





