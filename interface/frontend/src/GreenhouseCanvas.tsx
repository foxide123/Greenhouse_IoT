//import * as THREE from 'three';
import { Canvas } from '@react-three/fiber';
import { useGLTF, OrbitControls } from '@react-three/drei';

function Model() {
  const { scene } = useGLTF('../greenhouse_model/scene.gltf');
  return <primitive object={scene} />;
}

export default function GreenhouseCanvas() {
  return (
    <Canvas
      frameloop="demand"
      camera={{ position: [-20, 15, -25], fov: 30, near: 0.1, far: 100 }}
    >
      <ambientLight intensity={Math.PI / 2} />
      <spotLight
        position={[10, 10, 10]}
        angle={0.15}
        penumbra={1}
        decay={0}
        intensity={Math.PI}
      />
      <pointLight
        position={[-10, -10, -10]}
        decay={0}
        intensity={Math.PI}
      />
      <Model />
      <OrbitControls />
    </Canvas>
  );
}
