#pragma once

#include "UiInteractable.h"
#include "NodeChild.h"

#include <string>

#include <cinder\Rect.h>
#include <cinder\Color.h>

class CinderApp;
class ToolSet;
class Step;

class ToolButton : public UiInteractable, public NodeChild{
public:
	enum Type{
		NORMAL,
		TOGGLE,
		RADIO
	} type;
	
	ToolButton(Type _type, std::string _label, void (*_downCallback)(CinderApp * _app) = nullptr, void (*_upCallback)(CinderApp * _app) = nullptr);

	std::string label;
	
    // The function you want to call when you start clicking the button
	void (*downCallback)(CinderApp * _app);
    // The function you want to call when you finish clicking the button (press + release)
	void (*upCallback)(CinderApp * _app);

    // The function to be called when you are starting a click
	void downHandler(CinderApp * _app);
    // The fucntion to be called when you complete a click
	void upHandler(CinderApp * _app);

	void render(vox::MatrixStack * _matrixStack, RenderOptions * _renderStack) override;
};