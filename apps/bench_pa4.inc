/**
 *  Copyright 2019 Mike Reed
 */

#include "../include/GPath.h"

class GradientBench : public ShaderBench {
public:
    GradientBench(const GColor colors[], int count, const char* name, GTileMode mode = GTileMode::kClamp)
        : ShaderBench(name, 20)
    {
        fShader = GCreateLinearGradient({0, 0}, GPoint{W, H}, colors, count, mode);
    }
};

class PathBench : public GBenchmark {
    const char* fName;
    GPath       fPath;

public:
    enum { W = 100, H = 100 };

    PathBench(const char name[], float scale, bool clip) : fName(name) {
        GRandom rand;

        auto rp = [&]() {
            float x = rand.nextF() * W * scale;
            float y = rand.nextF() * H * scale;
            return GPoint{x, y};
        };

        constexpr int CTRS = 10;
        constexpr int PTS  = 10;
        for (int c = 0; c < CTRS; ++c) {
            fPath.moveTo(rp());
            for (int p = 0; p < PTS; ++p) {
                fPath.lineTo(rp());
            }
        }
        if (clip) {
            const auto r = fPath.bounds();
            fPath.offset((r.left + r.right) * 0.5f,
                         (r.top + r.bottom) * 0.5f);
        }
    }

    const char* name() const override { return fName; }
    GISize size() const override { return { W, H }; }
    void draw(GCanvas* canvas) override {
        for (int loops = 0; loops < 100; ++loops) {
            canvas->drawPath(fPath, GPaint());
        }
    }
};
