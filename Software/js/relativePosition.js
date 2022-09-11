export default class relativePosition {
  #vel = [0,0,0]
  #pos = [0,0,0]
  #posLowPass = [0,0,0]
  #interval
  #scale
  #alpha
  #beta
  #gamma

  constructor(interval=1/60, scale=20, alpha = 0.9, beta=0.98, gamma=0.9) {
    this.#interval = interval
    this.#scale = scale
    this.#alpha = alpha
    this.#beta = beta
    this.#gamma = gamma
  }

  update(acceleration) {
    let returnVal = [0,0,0]
    for (let i =0; i < 3; i++) {
      // Calculate velocity with exponential attenuation
      const acc = Math.atan(acceleration[i]/30)*30
      //const acc  = acceleration[i]
      this.#vel[i] = this.#alpha * this.#vel[i] + acc * this.#interval
      // Set max velocity to 100m/s
      this.#vel[i] = Math.atan(this.#vel[i]/100)*100
      // Calculate position with exponential attenuation
      this.#pos[i] = this.#beta * this.#pos[i] + this.#vel[i] * this.#interval
      // Set max position to 0.5 meters
      this.#pos[i] = Math.atan(this.#pos[i]/0.5)*0.5
      this.#posLowPass[i] = this.#gamma * this.#posLowPass[i] + (1-this.#gamma) * this.#pos[i]
      returnVal[i] = this.#posLowPass[i]*this.#scale
    }
    return [-returnVal[0],-returnVal[1],returnVal[2]]
  }
}