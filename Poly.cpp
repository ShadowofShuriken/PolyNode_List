#include <stdio.h>
#include<iostream>
#include "Poly.h"



PolyNode* CreatePoly(char* expr) {
	PolyNode* head = NULL;
	
	size_t size = strlen(expr) - 1;

	double coef = 0, tempc;
	int exp = 0, start = 0, temp = 0, tempe;
	bool sum = false, point = false, coefc = false;
	int i = start;
	while (i<size)
	{
		PolyNode* node = new PolyNode();
		node->next = NULL;
		PolyNode* p = head;
		PolyNode* q = NULL;
		exp = 0;
		coef = 0;
		do
		{
			if (expr[i] == '-')
			{
				sum = true;
				i++;
				start = i;
			}
			if (expr[i]=='.')
			{
				point = true;
				i++;
				start = i;
			}
			if (expr[i] == ' ')
			{
				i++;
				start = i;
			}
			else if (expr[i]=='x')
			{
				coefc = true;
				if (coef==0)
				{
					coef = 1;
				}
				break;
			}
			else
			{
				if (point==false)
				{
					tempc = (expr[i] - '0');
					for (int j = 0; j < i - start; j++)
					{
						coef = coef * 10;
					}
					coef = coef + tempc;
					i++;
					if (i>size)
					{
						break;
					}
				}
				else
				{
					tempc = (expr[i] - '0');
					for (int j = 0; j < i - start; j++)
					{
						tempc =  (tempc / 10);
					}
					coef = coef + tempc;
					i++; 
					if (i > size)
					{
						break;
					}
				}
			}
			
		} while (true);
		if (coef==0)
		{
			coef = 1;
		}
		if (sum==true)
		{
			coef = 0 - coef;
		}
		node->coef = coef;
		sum = false;
		point = false;
		
		i++;
		start = i;

		

		do
		{
			if (i<size)
			{
				if (expr[i] == '^')
				{
					i++;
					start = i;
					coefc = false;
				}
				if (expr[i] == '+' || expr[i] == '-' || expr[i] == ' ')
				{
					if (coefc == true)
					{
						exp = 1;
						coefc = false;
					}
					i++;
					start = i;
					break;
				}
				tempe = (expr[i] - '0');
				for (int j = 0; j < i - start; j++)
				{
					exp = exp * 10;
				}
				exp = exp + tempe;

				i++;
			}
			
			if (i >= size)
			{
				break;
			}
		} while (true);
		coefc = false;
		node->exp = exp;
		i++;
		start = i;
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}
		if (q == NULL)
		{
			node->next = head;
			head = node;
		}
		else
		{
			node->next = q->next;
			q->next = node;
		}
	}

	

	return head;
} //end-CreatePoly


void DeletePoly(PolyNode* poly) {
	while (poly != NULL)
	{
		PolyNode* node = poly;
		poly = poly->next;
		delete node;
	}
} // end-DeletePoly


PolyNode* AddNode(PolyNode* head, double coef, int exp) {
	PolyNode* node = new PolyNode();
	node->coef = coef;
	node->exp = exp;
	node->next = NULL;
	PolyNode* p = head;
	PolyNode* q = NULL;
	PolyNode* q1 = NULL;
	while (p != NULL && exp <= p->exp)
	{
		if (p->exp == exp)
		{
			q1 = p;
			break;
		}
		q1 = p;
		q = p;
		p = p->next;

	}
	if (q == NULL && q1 == NULL)
	{
		node->next = head;
		head = node;
	}
	else if (q1->exp == exp)
	{
		p->coef = p->coef + coef;
		if (p->coef == 0)
		{
			if (q == NULL)
			{
				head = p->next;
			}
			else
			{
				q->next = p->next;
			}
			delete p;
		}
	}
	else
	{
		node->next = q->next;
		q->next = node;
	}
	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* node = new PolyNode();
	PolyNode* head = NULL;
	PolyNode* q=NULL;
	PolyNode* p;
	PolyNode* q1 = NULL;
	PolyNode* p1;
	double coef;
	int exp;
	bool check = false;
	
	if (poly1->exp >= poly2->exp)
	{
		p = poly1;
		p1 = poly2;
	}
	else
	{
		p = poly2;
		p1 = poly1;
	}
		
	while (p!=NULL)
	{
		while (p1!=NULL&& p->exp <= p1->exp)
		{
			
			q1 = p1;
			p1 = p1->next;
		}
		if (q1==NULL)
		{
			check = true;
		}
		if (check==true)
		{
			coef = p->coef;
			exp = p->exp;
			check = false;
		}
		else
		{
			coef = p->coef + q1->coef;
			exp = p->exp;
			
		}
		q = p;
		p = p->next;
		node = AddNode(node, coef, exp);
		
	}
	return node;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* node = new PolyNode();
	PolyNode* head = NULL;
	PolyNode* q = NULL;
	PolyNode* p = poly1;
	PolyNode* q1 = NULL;
	PolyNode* p1 = poly2;
	double coef;
	int exp;
	bool check = false;


	while (p != NULL)
	{
		while (p1 != NULL && p->exp <= p1->exp)
		{

			q1 = p1;
			p1 = p1->next;
		}
		if (q1 == NULL)
		{
			check = true;
		}
		if (check == true)
		{
			coef = p->coef;
			exp = p->exp;
			check = false;
		}
		else
		{
			coef = p->coef - q1->coef;
			exp = p->exp;

		}
		q = p;
		p = p->next;
		node = AddNode(node, coef, exp);

	}
	return node;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* node = new PolyNode();
	PolyNode* head = NULL;
	PolyNode* q = NULL;
	PolyNode* p = poly1;
	PolyNode* q1 = NULL;
	PolyNode* p1 = poly2;
	double coef;
	int exp;
	bool check = false;


	while (p != NULL)
	{
		while (p1 != NULL)
		{
			coef = p->coef * p1->coef;
			exp = p->exp + p1->exp;
			node = AddNode(node, coef, exp);
			q1 = p1;
			p1 = p1->next;
		}
		q = p;
		p = p->next;
		p1 = poly2;
		
	}
	return node;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {
	double result = 0,temp=0;
	PolyNode* p = poly;

	while (p!=NULL)
	{
		temp = x;
		for (int i = 1; i < p->exp; i++)
		{
			temp = temp * x;
		}
		if (p->exp==0)
		{
			temp = p->coef;
		}
		else
		{
			temp = temp * p->coef;
		}
		
		result = temp + result;
		p = p->next;
	}
	
	return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
	PolyNode* node = new PolyNode();
	PolyNode* p = poly;
	PolyNode* q = NULL;
	double coef;
	int exp;
	while (p != NULL)
	{
		if (p->exp==0)
		{
			break;
		}
		else
		{
			coef = p->coef * p->exp;
			exp = p->exp - 1;
			node = AddNode(node, coef, exp);
		}
		q = p;
		p = p->next;
	}
	return node;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
	// Fill this in	
} //end-Plot
