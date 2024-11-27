#include "plugin.hpp"


struct Multiplier : Module {
	enum ParamId {
		C1_PARAM,
		C2_PARAM,
		C3_PARAM,
		C4_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		X1_INPUT,
		Y1_INPUT,
		X2_INPUT,
		Y2_INPUT,
		X3_INPUT,
		Y3_INPUT,
		X4_INPUT,
		Y4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		Z1_OUTPUT,
		Z2_OUTPUT,
		Z3_OUTPUT,
		Z4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Multiplier() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(C1_PARAM, 0.0, 1.0, 0.0, "");
		configParam(C2_PARAM, 0.0, 1.0, 0.0, "");
		configParam(C3_PARAM, 0.0, 1.0, 0.0, "");
		configParam(C4_PARAM, 0.0, 1.0, 0.0, "");
		configInput(X1_INPUT, "");
		configInput(Y1_INPUT, "");
		configInput(X2_INPUT, "");
		configInput(Y2_INPUT, "");
		configInput(X3_INPUT, "");
		configInput(Y3_INPUT, "");
		configInput(X4_INPUT, "");
		configInput(Y4_INPUT, "");
		configOutput(Z1_OUTPUT, "");
		configOutput(Z2_OUTPUT, "");
		configOutput(Z3_OUTPUT, "");
		configOutput(Z4_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		float o1 = inputs[X1_INPUT].getVoltage() * inputs[Y1_INPUT].getVoltage();
		float o2 = inputs[X2_INPUT].getVoltage() * inputs[Y2_INPUT].getVoltage();
		float o3 = inputs[X3_INPUT].getVoltage() * inputs[Y3_INPUT].getVoltage();
		float o4 = inputs[X4_INPUT].getVoltage() * inputs[Y4_INPUT].getVoltage();
		
		outputs[Z1_OUTPUT].setVoltage(o1 * params[C1_PARAM].getValue());
		outputs[Z2_OUTPUT].setVoltage(o2 * params[C2_PARAM].getValue());
		outputs[Z3_OUTPUT].setVoltage(o3 * params[C3_PARAM].getValue());
		outputs[Z4_OUTPUT].setVoltage(o4 * params[C4_PARAM].getValue());
	}
};


struct MultiplierWidget : ModuleWidget {
	MultiplierWidget(Multiplier* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Multiplier.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.687, 20.795)), module, Multiplier::C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.687, 52.042)), module, Multiplier::C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.687, 83.288)), module, Multiplier::C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.687, 115.012)), module, Multiplier::C4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 10.194)), module, Multiplier::X1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 20.795)), module, Multiplier::Y1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 41.44)), module, Multiplier::X2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 52.042)), module, Multiplier::Y2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 72.686)), module, Multiplier::X3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 83.288)), module, Multiplier::Y3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 104.411)), module, Multiplier::X4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(17.727, 115.012)), module, Multiplier::Y4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.687, 10.32)), module, Multiplier::Z1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.687, 41.567)), module, Multiplier::Z2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.687, 72.813)), module, Multiplier::Z3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.687, 104.537)), module, Multiplier::Z4_OUTPUT));
	}
};


Model* modelMultiplier = createModel<Multiplier, MultiplierWidget>("Multiplier");