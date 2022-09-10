export default class relativePosition {
  #vel = [100,0,0]
  #pos = [0,0,0]
  #posLowPass = [0,0,0]
  #interval
  #scale
  #alpha
  #beta
  #gamma

  constructor(interval=1/60, scale=100, alpha = 0.8, beta=0.95, gamma=0.98) {
    this.#interval = interval
    this.#scale = scale
    this.#alpha = alpha
    this.#beta = beta
    this.#gamma = gamma
  }

  update(acceleration) {
    let returnVal = [0,0,0]
    for (let i =0; i < 3; i++) {
      this.#vel[i] = this.#alpha * this.#vel[i] + acceleration[i] * this.#interval
      this.#pos[i] = this.#beta * this.#pos[i] + this.#vel[i] * this.#interval
      this.#pos[i] = Math.atan(this.#pos[i]/0.5)*0.5
      this.#posLowPass[i] = this.#gamma * this.#posLowPass[i] + (1-this.#gamma) * this.#pos[i]
      returnVal[i] = this.#posLowPass[i]*this.#scale
    }
    return [-returnVal[0],-returnVal[1],returnVal[2]]
  }
}