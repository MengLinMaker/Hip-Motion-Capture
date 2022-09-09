import '../css/style.css'

const sceneHeight = 2.8;





// Setting up three js canvas
import * as THREE from 'three';
const scene = new THREE.Scene();
scene.background = new THREE.Color( 0xffffff );
//scene.fog = new THREE.Fog( 0xffffff, 20, 60 );

const camera = new THREE.PerspectiveCamera(30, window.innerWidth/window.innerHeight, 0.1, 1000);
camera.up.set( 0, 0, 1 );
scene.position.set(0,0,sceneHeight);
camera.position.set( 24, 12, 12 );
const renderer = new THREE.WebGLRenderer({
  canvas: document.querySelector('#bg'),
});
renderer.setPixelRatio(window.devicePixelRatio);
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.render(scene, camera);
renderer.shadowMap.enabled = true;





// Autosize canvas
window.addEventListener('resize', onWindowResize, false)
onWindowResize()
function onWindowResize() {
  const container = document.getElementById('container');
  camera.aspect = container.clientWidth/ container.clientHeight;
  camera.updateProjectionMatrix();
  renderer.setSize( container.clientWidth, container.clientHeight );
  renderer.render(scene, camera);
}





// Importing orbit controls
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls';
const controls = new OrbitControls(camera, renderer.domElement);






// Defining lights
scene.add( new THREE.HemisphereLight( 0x443333, 0x111122 ) );
addShadowedLight( 10, 10, 50 + sceneHeight, 0xffffff, 2.5 );
addShadowedLight( 50, 0, - 50 + sceneHeight, 0xffccaa, 3 );
addShadowedLight( -10, -5, -10 + sceneHeight, 0xccaa88, 3 );
function addShadowedLight( x, y, z, color, intensity ) {
  const directionalLight = new THREE.DirectionalLight( color, intensity );
  directionalLight.position.set( x, y, z );
  scene.add( directionalLight );
  directionalLight.castShadow = true;
  const side = 10;
  directionalLight.shadow.camera.top = side;
  directionalLight.shadow.camera.bottom = -side;
  directionalLight.shadow.camera.left = side;
  directionalLight.shadow.camera.right = -side;
}





// Ground plane
//*/
const plane = new THREE.Mesh(
    new THREE.PlaneGeometry( 400, 400 ),
    new THREE.MeshPhysicalMaterial( { color: 0xfffffff } )
);
plane.translateZ(-10);
scene.add( plane );
plane.receiveShadow = true;
//*/






// Defining geometries
/*/
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';
import model from '../asset/hipModel.glb?url'

const loaderer = new GLTFLoader();
loaderer.load( model, function ( gltf ) {

	scene.add( gltf.scene );
  console.log(gltf)

}, undefined, function ( error ) {

	console.error( error );

} );
//*/

import { STLLoader } from 'three/examples/jsm/loaders/STLLoader'
const loader = new STLLoader();
const material = new THREE.MeshPhysicalMaterial( { color: 0xaa8866, clearcoat: 0.8, roughness: 0.5, clearcoatRoughness: 0.5 } );

let hip;
import hipSTL from '../asset/hip.stl?url'
loader.load(
  hipSTL,
  function (geometry) {
    geometry.center();
    const mesh = new THREE.Mesh( geometry, material );
    mesh.castShadow = true;
    mesh.receiveShadow = true;

    mesh.scale.set( -0.01, 0.01, 0.01 );
    hip = mesh;
    scene.add(mesh);

    loadRightThigh();
    loadLeftThigh();
  }
)

let rightThigh;
import rightThighSTL from '../asset/rightThigh.stl?url'
function loadRightThigh(){
  loader.load(
    rightThighSTL,
    function (geometry) {
      geometry.center();
      const mesh = new THREE.Mesh( geometry, material );
      mesh.castShadow = true;
      mesh.receiveShadow = true;

      geometry.translate( 0, 20, -215 );
      mesh.position.set( -10, -80, -10 );
      mesh.scale.set( 1, -1, 1 );
      rightThigh = mesh;
      hip.add(rightThigh);
    }
  )
}

let leftThigh;
import leftThighSTL from '../asset/rightThigh.stl?url'
function loadLeftThigh(){
  loader.load(
    leftThighSTL,
    function (geometry) {
      geometry.center();
      const mesh = new THREE.Mesh( geometry, material );
      mesh.castShadow = true;
      mesh.receiveShadow = true;

      geometry.translate( 0, 20, -215 );
      mesh.position.set( -10, 80, -10 );
      mesh.scale.set( 1, 1, 1 );
      leftThigh = mesh;
      hip.add(leftThigh);
    }
  )
}






// helper functions
//scene.add(new THREE.AxesHelper(3.5));

// Rendering and animate at set fps
let clock = new THREE.Clock();
let delta = 0;
let interval = 1 / 60;
function animate() {
  requestAnimationFrame(animate);
  delta += clock.getDelta();
  if (delta  > interval) {



    if (hip != null && rightThigh != null && leftThigh != null){
      if (window.currentData != null) animateData();
      else walkingAnimation();
      controls.update();
      renderer.render(scene, camera);
      delta = delta % interval;
    }



  }
}
animate();



// Animate the data
let q, qh, qr, ql;
let vel = 0.5;
let pos = 0;
let posLowPass = 0;
const alpha = 0.8;
const beta = 0.95;
const gamma = 0.98;
function animateData(){
  const data = window.currentData;
  qh = new THREE.Quaternion(data[7], data[8], data[9], data[6]).normalize();

  const vector = new THREE.Vector3(data[3], data[4], data[5]);
  vector.applyQuaternion(qh);

  vel = alpha*vel + (vector.z-9.81)*interval
  pos = beta*pos + vel*interval
  
  posLowPass = gamma*posLowPass + (1-gamma)*pos
  hip.position.z = posLowPass*100

  hip.rotation.setFromQuaternion(qh);
  qh = new THREE.Quaternion(data[7], -data[8], -data[9], -data[6]).normalize();
  
  q = new THREE.Quaternion(data[17], -data[18], -data[19], data[16]).normalize();
  qr = new THREE.Quaternion().multiplyQuaternions(qh,q).normalize();
  rightThigh.rotation.setFromQuaternion(qr);

  q = new THREE.Quaternion(data[27], -data[28], -data[29], data[26]).normalize();
  ql = new THREE.Quaternion().multiplyQuaternions(qh,q).normalize();
  leftThigh.rotation.setFromQuaternion(ql);

  const hipUp = data[5]**2 / (data[5]**2+data[4]**2+data[3]**2)
  const rightThighUp = data[15]**2/ (data[15]**2+data[14]**2+data[13]**2)
  const leftthighUp = data[25]**2 / (data[25]**2+data[24]**2+data[23]**2)
  const standingIndex = hipUp * rightThighUp * leftthighUp
  console.log(standingIndex.toFixed(1))
}



// Making a walking animation
let counter = 0;
const speed = 1.1;
function walkingAnimation(){
  counter += Math.PI*interval*speed;
  const sc = Math.sin(counter);

  hip.rotation.z += Math.PI/4*interval*Math.sqrt(speed);
  hip.rotation.x = 0.08*sc;
  hip.position.z = 0.2*sc;

  q = new THREE.Quaternion(0.05,0.18,0,sc-0.2);
  leftThigh.rotation.setFromQuaternion(q);
  q = new THREE.Quaternion(0.05,0.18,0,-sc-0.2);
  rightThigh.rotation.setFromQuaternion(q);
}


