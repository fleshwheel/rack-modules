#include "plugin.hpp"


struct Oscillator : Module {
	enum ParamId {
		FM0_PARAM,
		F0_PARAM,
		AM0_PARAM,
		A0_PARAM,
		FM1_PARAM,
		F1_PARAM,
		AM1_PARAM,
		A1_PARAM,
		FM2_PARAM,
		F2_PARAM,
		AM2_PARAM,
		A2_PARAM,
		FM3_PARAM,
		F3_PARAM,
		AM3_PARAM,
		A3_PARAM,
		FM4_PARAM,
		F4_PARAM,
		AM4_PARAM,
		A4_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		FM0_INPUT,
		AM0_INPUT,
		FM1_INPUT,
		AM1_INPUT,
		FM2_INPUT,
		AM2_INPUT,
		FM3_INPUT,
		AM3_INPUT,
		FM4_INPUT,
		AM4_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SIN0_OUTPUT,
		COS0_OUTPUT,
		SIN1_OUTPUT,
		COS1_OUTPUT,
		SIN2_OUTPUT,
		COS2_OUTPUT,
		SIN3_OUTPUT,
		COS3_OUTPUT,
		SIN4_OUTPUT,
		COS4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Oscillator() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(FM0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AM0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FM1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AM1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FM2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AM2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FM3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AM3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FM4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AM4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A4_PARAM, 0.f, 1.f, 0.f, "");
		configInput(FM0_INPUT, "");
		configInput(AM0_INPUT, "");
		configInput(FM1_INPUT, "");
		configInput(AM1_INPUT, "");
		configInput(FM2_INPUT, "");
		configInput(AM2_INPUT, "");
		configInput(FM3_INPUT, "");
		configInput(AM3_INPUT, "");
		configInput(FM4_INPUT, "");
		configInput(AM4_INPUT, "");
		configOutput(SIN0_OUTPUT, "");
		configOutput(COS0_OUTPUT, "");
		configOutput(SIN1_OUTPUT, "");
		configOutput(COS1_OUTPUT, "");
		configOutput(SIN2_OUTPUT, "");
		configOutput(COS2_OUTPUT, "");
		configOutput(SIN3_OUTPUT, "");
		configOutput(COS3_OUTPUT, "");
		configOutput(SIN4_OUTPUT, "");
		configOutput(COS4_OUTPUT, "");
	}
	
	double p0 = 0.0;
	double p1 = 0.0;
	double p2 = 0.0;
	double p3 = 0.0;
	double p4 = 0.0;
	void process(const ProcessArgs& args) override {
		double f0 = params[F0_PARAM].getValue() + params[FM0_PARAM].getValue() * inputs[FM0_INPUT].getVoltage();
		double f1 = params[F1_PARAM].getValue() + params[FM1_PARAM].getValue() * inputs[FM1_INPUT].getVoltage();
		double f2 = params[F2_PARAM].getValue() + params[FM2_PARAM].getValue() * inputs[FM2_INPUT].getVoltage();
		double f3 = params[F3_PARAM].getValue() + params[FM3_PARAM].getValue() * inputs[FM3_INPUT].getVoltage();
		double f4 = params[F4_PARAM].getValue() + params[FM4_PARAM].getValue() * inputs[FM4_INPUT].getVoltage();
		
		double a0 = params[A0_PARAM].getValue() + params[AM0_PARAM].getValue() * inputs[AM0_INPUT].getVoltage();
		double a1 = params[A1_PARAM].getValue() + params[AM1_PARAM].getValue() * inputs[AM1_INPUT].getVoltage();
		double a2 = params[A2_PARAM].getValue() + params[AM2_PARAM].getValue() * inputs[AM2_INPUT].getVoltage();
		double a3 = params[A3_PARAM].getValue() + params[AM3_PARAM].getValue() * inputs[AM3_INPUT].getVoltage();
		double a4 = params[A4_PARAM].getValue() + params[AM4_PARAM].getValue() * inputs[AM4_INPUT].getVoltage();		
		
		p0 += f0 * args.sampleTime;
		if (p0 >= 1.0) { p0 -= 1.0; }
		p1 += f1 * args.sampleTime;
		if (p1 >= 1.0) { p1 -= 1.0; }
		p2 += f2 * args.sampleTime;
		if (p2 >= 1.0) { p2 -= 1.0; }
		p3 += f3 * args.sampleTime;
		if (p3 >= 1.0) { p3 -= 1.0; }
		p4 += f4 * args.sampleTime;
		if (p4 >= 1.0) { p4 -= 1.0; }
		
		double sin0 = std::sin(2.f * M_PI * p0 * 2048.0) * a0;
		double sin1 = std::sin(2.f * M_PI * p1 * 2048.0) * a1;
		double sin2 = std::sin(2.f * M_PI * p2 * 2048.0) * a2;
		double sin3 = std::sin(2.f * M_PI * p3 * 2048.0) * a3;
		double sin4 = std::sin(2.f * M_PI * p4 * 2048.0) * a4;

		double cos0 = std::cos(2.f * M_PI * p0 * 2048.0) * a0;
		double cos1 = std::cos(2.f * M_PI * p1 * 2048.0) * a1;
		double cos2 = std::cos(2.f * M_PI * p2 * 2048.0) * a2;
		double cos3 = std::cos(2.f * M_PI * p3 * 2048.0) * a3;
		double cos4 = std::cos(2.f * M_PI * p4 * 2048.0) * a4;

		outputs[SIN0_OUTPUT].setVoltage(sin0);
		outputs[SIN1_OUTPUT].setVoltage(sin1);
		outputs[SIN2_OUTPUT].setVoltage(sin2);
		outputs[SIN3_OUTPUT].setVoltage(sin3);
		outputs[SIN4_OUTPUT].setVoltage(sin4);
		
		outputs[COS0_OUTPUT].setVoltage(cos0);
		outputs[COS1_OUTPUT].setVoltage(cos1);
		outputs[COS2_OUTPUT].setVoltage(cos2);
		outputs[COS3_OUTPUT].setVoltage(cos3);
		outputs[COS4_OUTPUT].setVoltage(cos4);		
	}
};


struct OscillatorWidget : ModuleWidget {
	OscillatorWidget(Oscillator* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Oscillator.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 12.251)), module, Oscillator::FM0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 12.104)), module, Oscillator::F0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 21.928)), module, Oscillator::AM0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 21.928)), module, Oscillator::A0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 37.261)), module, Oscillator::FM1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 37.113)), module, Oscillator::F1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 46.937)), module, Oscillator::AM1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 46.937)), module, Oscillator::A1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 60.25)), module, Oscillator::FM2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 60.102)), module, Oscillator::F2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 69.926)), module, Oscillator::AM2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 69.926)), module, Oscillator::A2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 83.921)), module, Oscillator::FM3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 83.774)), module, Oscillator::F3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 93.598)), module, Oscillator::AM3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 93.598)), module, Oscillator::A3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 108.416)), module, Oscillator::FM4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 108.269)), module, Oscillator::F4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.525, 118.093)), module, Oscillator::AM4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.153, 118.093)), module, Oscillator::A4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 12.251)), module, Oscillator::FM0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 21.928)), module, Oscillator::AM0_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 37.261)), module, Oscillator::FM1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 46.937)), module, Oscillator::AM1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 60.25)), module, Oscillator::FM2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 69.926)), module, Oscillator::AM2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 83.921)), module, Oscillator::FM3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 93.598)), module, Oscillator::AM3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 108.416)), module, Oscillator::FM4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.177, 118.093)), module, Oscillator::AM4_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 12.104)), module, Oscillator::SIN0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 21.78)), module, Oscillator::COS0_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 37.113)), module, Oscillator::SIN1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 46.79)), module, Oscillator::COS1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 60.102)), module, Oscillator::SIN2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 69.779)), module, Oscillator::COS2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 83.774)), module, Oscillator::SIN3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 93.45)), module, Oscillator::COS3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 108.269)), module, Oscillator::SIN4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(46.924, 117.946)), module, Oscillator::COS4_OUTPUT));
	}
};


Model* modelOscillator = createModel<Oscillator, OscillatorWidget>("Oscillator");