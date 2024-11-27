#include "plugin.hpp"


struct Magnitude : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		RE0_INPUT,
		IM0_INPUT,
		RE1_INPUT,
		IM1_INPUT,
		RE2_INPUT,
		IM2_INPUT,
		RE3_INPUT,
		IM3_INPUT,
		RE4_INPUT,
		IM4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		MAG0_OUTPUT,
		MAG1_OUTPUT,
		MAG2_OUTPUT,
		MAG3_OUTPUT,
		MAG4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Magnitude() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(RE0_INPUT, "");
		configInput(IM0_INPUT, "");
		configInput(RE1_INPUT, "");
		configInput(IM1_INPUT, "");
		configInput(RE2_INPUT, "");
		configInput(IM2_INPUT, "");
		configInput(RE3_INPUT, "");
		configInput(IM3_INPUT, "");
		configInput(RE4_INPUT, "");
		configInput(IM4_INPUT, "");
		configOutput(MAG0_OUTPUT, "");
		configOutput(MAG1_OUTPUT, "");
		configOutput(MAG2_OUTPUT, "");
		configOutput(MAG3_OUTPUT, "");
		configOutput(MAG4_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {		
		outputs[MAG0_OUTPUT].setVoltage(std::sqrt(std::pow(inputs[RE0_INPUT].getVoltage(), 2) + std::pow(inputs[IM0_INPUT].getVoltage(), 2)));
		outputs[MAG0_OUTPUT].setVoltage(std::sqrt(std::pow(inputs[RE0_INPUT].getVoltage(), 2) + std::pow(inputs[IM0_INPUT].getVoltage(), 2)));
		outputs[MAG2_OUTPUT].setVoltage(std::sqrt(std::pow(inputs[RE0_INPUT].getVoltage(), 2) + std::pow(inputs[IM0_INPUT].getVoltage(), 2)));
		outputs[MAG3_OUTPUT].setVoltage(std::sqrt(std::pow(inputs[RE0_INPUT].getVoltage(), 2) + std::pow(inputs[IM0_INPUT].getVoltage(), 2)));
		outputs[MAG4_OUTPUT].setVoltage(std::sqrt(std::pow(inputs[RE0_INPUT].getVoltage(), 2) + std::pow(inputs[IM0_INPUT].getVoltage(), 2)));
		
		
	}
};


struct MagnitudeWidget : ModuleWidget {
	MagnitudeWidget(Magnitude* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Magnitude.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 8.234)), module, Magnitude::RE0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 17.835)), module, Magnitude::IM0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 34.036)), module, Magnitude::RE1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 43.637)), module, Magnitude::IM1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 58.397)), module, Magnitude::RE2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 67.999)), module, Magnitude::IM2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 85.721)), module, Magnitude::RE3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 95.323)), module, Magnitude::IM3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 111.149)), module, Magnitude::RE4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.997, 120.751)), module, Magnitude::IM4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.699, 8.086)), module, Magnitude::MAG0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.699, 33.888)), module, Magnitude::MAG1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.699, 58.25)), module, Magnitude::MAG2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.699, 85.574)), module, Magnitude::MAG3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.699, 111.002)), module, Magnitude::MAG4_OUTPUT));
	}
};


Model* modelMagnitude = createModel<Magnitude, MagnitudeWidget>("Magnitude");