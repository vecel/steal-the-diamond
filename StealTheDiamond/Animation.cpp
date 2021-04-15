#include "Animation.h"

Animation::Animation(Object* target) {
	this->target = target;
	totalLength = progress = 0.0;
}

Animation::~Animation() {

}

void Animation::addFrame(Frame&& frame) {
	frames.push_back(std::move(frame));
	totalLength += frame.duration;
}

void Animation::update(double elapsedTime) {
	progress = elapsedTime;
	double p = progress;
	for (int i = 0; i < frames.size(); ++i) {
		p -= frames[i].duration;

		if (p <= 0.0 || &frames[i] == &(frames.back())) {
			target->sprite.setTextureRect(frames[i].frameRect);
			break;
		}
	}
}

double Animation::getLength() { return totalLength; }