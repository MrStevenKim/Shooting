#include "iImage.h"

#include "iStd.h"

iImage::iImage()
{
	arrayTex = new iArray(freeTex);
	tex = NULL;
	position = iPointMake(0, 0);

	selected = false;
	selectedDt = 0.0f;
	_selectedDt = default_selectedDt;
	selectedScale = default_selectedScale;

	animation = false;
	aniDt = 0.0f;
	_aniDt = 0.08f;
	frame = 0;
	repeatNum = 0;// inf
	method = NULL;
}

iImage::~iImage()
{
	delete arrayTex;
}

void iImage::freeTex(void* data)
{
	Texture* tex = (Texture*)data;
	if (tex->retainCount > 1)
	{
		tex->retainCount--;
		return;
	}
	freeImage(tex);
}

void iImage::addObject(Texture* tex)
{
	arrayTex->addObject(tex);
	tex->retainCount++;
	if (this->tex == NULL)
		this->tex = tex;
}

void iImage::setTexAtIndex(int index)
{
	Texture* tex = (Texture*)arrayTex->objectAtIndex(index);
	if (tex)
	{
		this->tex = tex;
		frame = index;
	}
}

void iImage::replaceAtIndex(int index, Texture* tex)
{
	Texture* t = (Texture*)arrayTex->objectAtIndex(index);
#if 0
	arrayTex->remove(index);
	arrayTex->addObject(index, tex);
	if (this->tex == t)
		this->tex = tex;
#else
	//freeImage(t);
	if (t->retainCount > 1)
		t->retainCount--;
	else
		delete (Image*)t->texID;
	memcpy(t, tex, sizeof(Texture));
	free(tex);
#endif
}

void iImage::paint(float dt, iPoint off)
{
	if (animation)
	{
		aniDt += dt;
		if (aniDt < _aniDt)
		{
			;
		}
		else
		{
			aniDt -= _aniDt;
			frame++;
			if (frame == arrayTex->count)
			{
				if( repeatNum==0 )
					frame = 0;
				else
				{
					if (method)
						method(this);
					if (lastFrame)
						frame = arrayTex->count - 1;
					else
						frame = 0;
					animation = false;
				}
				tex = (Texture*)arrayTex->objectAtIndex(frame);
			}
		}
	}

	if (selected)
	{
		selectedDt += dt;
		if (selectedDt > _selectedDt)
			selectedDt = _selectedDt;
	}
	else
	{
		selectedDt -= dt;
		if (selectedDt < 0.0f)
			selectedDt = 0.0f;
	}
	iPoint p = position + off;
	float s = 1.0f + linear(selectedDt / _selectedDt, 0.0f, selectedScale);
	if (s == 0.0f)
	{
		drawImage(tex, p.x, p.y, TOP | LEFT);
	}
	else
	{
		p.x += tex->width / 2;
		p.y += tex->height / 2;
		drawImage(tex, p.x, p.y, 0, 0, tex->width, tex->height,
			VCENTER | HCENTER, s, s, 2, 0, REVERSE_NONE);
	}
}

void iImage::startAnimation(IMAGE_METHOD m)
{
	animation = true;
	method = m;
	aniDt = 0.0f;
	frame = 0;
}

iRect iImage::touchRect(iPoint p)
{
	p += position;
	iRect rt = iRectMake(p.x, p.y,
						tex->width, tex->height);
	return rt;
}
