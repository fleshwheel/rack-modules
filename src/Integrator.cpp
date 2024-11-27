#include "plugin.hpp"


struct Integrator : Module {
	enum ParamId {
		F1_PARAM,
		F2_PARAM,
		F3_PARAM,
		F4_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		X1_INPUT,
		F1_INPUT,
		X2_INPUT,
		F2_INPUT,
		X3_INPUT,
		F3_INPUT,
		X4_INPUT,
		F4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		Y1_OUTPUT,
		Y2_OUTPUT,
		Y3_OUTPUT,
		Y4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Integrator() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(F1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F4_PARAM, 0.f, 1.f, 0.f, "");
		configInput(X1_INPUT, "");
		configInput(F1_INPUT, "");
		configInput(X2_INPUT, "");
		configInput(F2_INPUT, "");
		configInput(X3_INPUT, "");
		configInput(F3_INPUT, "");
		configInput(X4_INPUT, "");
		configInput(F4_INPUT, "");
		configOutput(Y1_OUTPUT, "");
		configOutput(Y2_OUTPUT, "");
		configOutput(Y3_OUTPUT, "");
		configOutput(Y4_OUTPUT, "");
	}

	// accumulators for integration.
	// bounded by +/- 5V.
	float a1 = 0.f;
	float a2 = 0.f;
	float a3 = 0.f;
	float a4 = 0.f;
	void process(const ProcessArgs& args) override {
		
		float c1 = params[F1_PARAM].getValue();
		if (inputs[F1_INPUT].isConnected()) { c1 *= inputs[F1_INPUT].getVoltage(); }
		float c2 = params[F2_PARAM].getValue();
		if (inputs[F2_INPUT].isConnected()) { c2 *= inputs[F2_INPUT].getVoltage(); }
		float c3 = params[F3_PARAM].getValue();
		if (inputs[F3_INPUT].isConnected()) { c3 *= inputs[F3_INPUT].getVoltage(); }
		float c4 = params[F4_PARAM].getValue();
		if (inputs[F4_INPUT].isConnected()) { c4 *= inputs[F4_INPUT].getVoltage(); }
		
		a1 += inputs[X1_INPUT].getVoltage() * args.sampleTime * c1 * 64;
		a2 += inputs[X2_INPUT].getVoltage() * args.sampleTime * c2 * 64;
		a3 += inputs[X3_INPUT].getVoltage() * args.sampleTime * c3 * 64;
		a4 += inputs[X4_INPUT].getVoltage() * args.sampleTime * c4 * 64;
		
		if (a1 > 5.0) { a1 = 5.0; }
		if (a1 < -5.0) { a1 = -5.0; }
		if (a2 > 5.0) { a2 = 5.0; }
		if (a2 < -5.0) { a2 = -5.0; }
		if (a3 > 5.0) { a3 = 5.0; }
		if (a3 < -5.0) { a3 = -5.0; }
		if (a4 > 5.0) { a4 = 5.0; }
		if (a4 < -5.0) { a4 = -5.0; }
		
		outputs[Y1_OUTPUT].setVoltage(a1);
		outputs[Y2_OUTPUT].setVoltage(a2);
		outputs[Y3_OUTPUT].setVoltage(a3);
		outputs[Y4_OUTPUT].setVoltage(a4);
	}
};


struct IntegratorWidget : ModuleWidget {
	IntegratorWidget(Integrator* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Integrator.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.02, 18.639)), module, Integrator::F1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.02, 49.885)), module, Integrator::F2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.02, 81.131)), module, Integrator::F3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.02, 112.856)), module, Integrator::F4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 8.037)), module, Integrator::X1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 18.639)), module, Integrator::F1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 39.284)), module, Integrator::X2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 49.885)), module, Integrator::F2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 70.53)), module, Integrator::X3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 81.131)), module, Integrator::F3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 102.254)), module, Integrator::X4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.06, 112.856)), module, Integrator::F4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.02, 8.164)), module, Integrator::Y1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.02, 39.41)), module, Integrator::Y2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.02, 70.656)), module, Integrator::Y3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.02, 102.381)), module, Integrator::Y4_OUTPUT));
	}
};


Model* modelIntegrator = createModel<Integrator, IntegratorWidget>("Integrator");