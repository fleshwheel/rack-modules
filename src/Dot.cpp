#include "plugin.hpp"
#define clamp(x) if (x > 5.0) { x = 5.0; } else if (x < -5.0) { x = -5.0; }

struct Dot : Module {
	enum ParamId {
		A0_PARAM,
		C0_PARAM,
		A1_PARAM,
		C1_PARAM,
		A2_PARAM,
		C2_PARAM,
		A3_PARAM,
		C3_PARAM,
		A4_PARAM,
		C4_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		IN0L_INPUT,
		IN0R_INPUT,
		IN1L_INPUT,
		IN1R_INPUT,
		IN2L_INPUT,
		IN2R_INPUT,
		IN3L_INPUT,
		IN3R_INPUT,
		IN4L_INPUT,
		IN4R_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT0L_OUTPUT,
		OUT0R_OUTPUT,
		OUT1L_OUTPUT,
		OUT1R_OUTPUT,
		OUT2L_OUTPUT,
		OUT2R_OUTPUT,
		OUT3L_OUTPUT,
		OUT3R_OUTPUT,
		CHAIN_OUTPUT,
		OUT4L_OUTPUT,
		OUT4R_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Dot() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(A0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C4_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_INPUT, "");
		configInput(IN0L_INPUT, "");
		configInput(IN0R_INPUT, "");
		configInput(IN1L_INPUT, "");
		configInput(IN1R_INPUT, "");
		configInput(IN2L_INPUT, "");
		configInput(IN2R_INPUT, "");
		configInput(IN3L_INPUT, "");
		configInput(IN3R_INPUT, "");
		configInput(IN4L_INPUT, "");
		configInput(IN4R_INPUT, "");
		configOutput(OUT0L_OUTPUT, "");
		configOutput(OUT0R_OUTPUT, "");
		configOutput(OUT1L_OUTPUT, "");
		configOutput(OUT1R_OUTPUT, "");
		configOutput(OUT2L_OUTPUT, "");
		configOutput(OUT2R_OUTPUT, "");
		configOutput(OUT3L_OUTPUT, "");
		configOutput(OUT3R_OUTPUT, "");
		configOutput(CHAIN_OUTPUT, "");
		configOutput(OUT4L_OUTPUT, "");
		configOutput(OUT4R_OUTPUT, "");
	}
	
	// accumulators for integration.
	// bounded by +/- 5V using clamp
	// macro.
	double i0l = 0.0;
	double i1l = 0.0;
	double i2l = 0.0;
	double i3l = 0.0;
	double i4l = 0.0;
	
	double i0r = 0.0;
	double i1r = 0.0;
	double i2r = 0.0;
	double i3r = 0.0;
	double i4r = 0.0;
	
	void process(const ProcessArgs& args) override {
		double in = inputs[IN_INPUT].getVoltage();
		
		double v0l = in * inputs[IN0L_INPUT].getVoltage();
		double v1l = in * inputs[IN1L_INPUT].getVoltage();
		double v2l = in * inputs[IN2L_INPUT].getVoltage();
		double v3l = in * inputs[IN3L_INPUT].getVoltage();
		double v4l = in * inputs[IN4L_INPUT].getVoltage();
		
		double v0r = in * inputs[IN0R_INPUT].getVoltage();
		double v1r = in * inputs[IN1R_INPUT].getVoltage();
		double v2r = in * inputs[IN2R_INPUT].getVoltage();
		double v3r = in * inputs[IN3R_INPUT].getVoltage();
		double v4r = in * inputs[IN4R_INPUT].getVoltage();
		
		double c0 = std::pow(params[C0_PARAM].getValue(), 0.005);
		double c1 = std::pow(params[C1_PARAM].getValue(), 0.005);
		double c2 = std::pow(params[C2_PARAM].getValue(), 0.005);
		double c3 = std::pow(params[C3_PARAM].getValue(), 0.005);
		double c4 = std::pow(params[C4_PARAM].getValue(), 0.005);
		
		i0l = (i0l * c0) + v0l * args.sampleTime * params[A0_PARAM].getValue() * 64;
		i1l = (i1l * c1) + v1l * args.sampleTime * params[A1_PARAM].getValue() * 64;
		i2l = (i2l * c2) + v2l * args.sampleTime * params[A2_PARAM].getValue() * 64;
		i3l = (i3l * c3) + v3l * args.sampleTime * params[A3_PARAM].getValue() * 64;
		i4l = (i4l * c4) + v4l * args.sampleTime * params[A4_PARAM].getValue() * 64;
		
		i0r = (i0r * c0) + v0r * args.sampleTime * params[A0_PARAM].getValue() * 64;
		i1r = (i1r * c1) + v1r * args.sampleTime * params[A1_PARAM].getValue() * 64;
		i2r = (i2r * c2) + v2r * args.sampleTime * params[A2_PARAM].getValue() * 64;
		i3r = (i3r * c3) + v3r * args.sampleTime * params[A3_PARAM].getValue() * 64;
		i4r = (i4r * c4) + v4r * args.sampleTime * params[A4_PARAM].getValue() * 64;
		
		clamp(i0l);
		clamp(i1l);
		clamp(i2l);
		clamp(i3l);
		clamp(i4l);
		
		clamp(i0r);
		clamp(i1r);
		clamp(i2r);
		clamp(i3r);
		clamp(i4r);

		outputs[OUT0L_OUTPUT].setVoltage(i0l);
		outputs[OUT1L_OUTPUT].setVoltage(i1l);
		outputs[OUT2L_OUTPUT].setVoltage(i2l);
		outputs[OUT3L_OUTPUT].setVoltage(i3l);
		outputs[OUT4L_OUTPUT].setVoltage(i4l);
		
		outputs[OUT0R_OUTPUT].setVoltage(i0r);
		outputs[OUT1R_OUTPUT].setVoltage(i1r);
		outputs[OUT2R_OUTPUT].setVoltage(i2r);
		outputs[OUT3R_OUTPUT].setVoltage(i3r);
		outputs[OUT4R_OUTPUT].setVoltage(i4r);
		
		// for daisy chaining
		outputs[CHAIN_OUTPUT].setVoltage(in);
		
	}
};


struct DotWidget : ModuleWidget {
	DotWidget(Dot* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Dot.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.443, 7.484)), module, Dot::A0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.761, 18.085)), module, Dot::C0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.654, 34.756)), module, Dot::A1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.972, 45.358)), module, Dot::C1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.865, 59.425)), module, Dot::A2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.183, 70.026)), module, Dot::C2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.076, 86.412)), module, Dot::A3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.394, 97.013)), module, Dot::C3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.361, 110.794)), module, Dot::A4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.679, 121.396)), module, Dot::C4_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.174, 7.484)), module, Dot::IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.403, 7.61)), module, Dot::IN0L_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.479, 7.61)), module, Dot::IN0R_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.614, 34.883)), module, Dot::IN1L_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.69, 34.883)), module, Dot::IN1R_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.825, 59.551)), module, Dot::IN2L_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(53.901, 59.551)), module, Dot::IN2R_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.035, 86.538)), module, Dot::IN3L_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(54.112, 86.538)), module, Dot::IN3R_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.321, 110.921)), module, Dot::IN4L_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(54.397, 110.921)), module, Dot::IN4R_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(34.614, 18.085)), module, Dot::OUT0L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.69, 18.085)), module, Dot::OUT0R_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(34.825, 45.358)), module, Dot::OUT1L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.901, 45.358)), module, Dot::OUT1R_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35.035, 70.026)), module, Dot::OUT2L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(54.112, 70.026)), module, Dot::OUT2R_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35.246, 97.013)), module, Dot::OUT3L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(54.323, 97.013)), module, Dot::OUT3R_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(6.25, 120.073)), module, Dot::CHAIN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35.532, 121.396)), module, Dot::OUT4L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(54.608, 121.396)), module, Dot::OUT4R_OUTPUT));
	}
};


Model* modelDot = createModel<Dot, DotWidget>("Dot");