import './index.css';
import React, { useState, useRef } from 'react';
import { Contenedor_Principal, Contenedor_Secundario } from './components/shared/Funciones';

function App() {

  // Html del login
  const Login = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');

    const usernameRef = useRef(null);
    const passwordRef = useRef(null);

    function handleLogin(event) {
      event.preventDefault();
      // Add login logic here
      sessionStorage.setItem('user_name', username);
      sessionStorage.setItem('user_type', 'User');
      window.location.reload();
      console.log('Login button clicked!');
    }

    return (
      <form>
        <h1 className="text-center">Login</h1>
        <br /><hr className="Principal" /><br />
        <div className="form-group">
          <label htmlFor="username">Username</label>
          <input
            type="text"
            id="username"
            className="form-control mx-auto text-center w-50"
            value={username}
            onChange={(event) => setUsername(event.target.value)}
            ref={usernameRef}
          />
        </div>
        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            id="password"
            className="form-control mx-auto text-center w-50"
            value={password}
            onChange={(event) => setPassword(event.target.value)}
            ref={passwordRef}
          />
        </div>
        <br />
        <button className="btn boton mx-auto text-center w-50" onClick={(event) => handleLogin(event)}>Login</button>
      </form>
    );
  };

  // Html del registro para nuevos usuarios
  const Registro = () => {
    const [nombreCompleto, setNombreCompleto] = useState('');
    const [username, setUsername] = useState('');
    const [fotoPerfil, setFotoPerfil] = useState('https://via.placeholder.com/150');
    const [correoElectronico, setCorreoElectronico] = useState('');
    const [contrasena, setContrasena] = useState('');
    const [confirmarContrasena, setConfirmarContrasena] = useState('');

    const handleRegistro = (event) => {
      event.preventDefault();
      // Aquí puedes agregar la lógica para enviar los datos del formulario a tu backend

      console.log('Registro exitoso!');
    };

    return (
      <form onSubmit={handleRegistro}>
        <h1 className="text-center">Registro</h1>
        <br /><hr className="Principal" /><br />
        <div className="form-group">
          <label htmlFor="nombreCompleto">Nombre Completo</label>
          <input
            type="text"
            id="nombreCompleto"
            className="form-control mx-auto text-center w-50"
            value={nombreCompleto}
            onChange={(event) => setNombreCompleto(event.target.value)}
          />
        </div>
        <div className="form-group">
          <label htmlFor="username">Username</label>
          <input
            type="text"
            id="username"
            className="form-control mx-auto text-center w-50"
            value={username}
            onChange={(event) => setUsername(event.target.value)}
          />
        </div>
        <div className="form-group">
          <label htmlFor="fotoPerfil">Foto de perfil</label>
          <br />
          <img src={fotoPerfil} alt="Foto de perfil" />
          <br /><br />
          <input
            type="file"
            id="fotoPerfil"
            className="form-control mx-auto text-center w-50"
            onChange={(event) => setFotoPerfil(event.target.files[0])}
          />
        </div>
        <div className="form-group">
          <label htmlFor="correoElectronico">Correo electrónico</label>
          <input
            type="email"
            id="correoElectronico"
            className="form-control mx-auto text-center w-50"
            value={correoElectronico}
            onChange={(event) => setCorreoElectronico(event.target.value)}
          />
        </div>
        <div className="form-group">
          <label htmlFor="contrasena">Contraseña</label>
          <input
            type="password"
            id="contrasena"
            className="form-control mx-auto text-center w-50"
            value={contrasena}
            onChange={(event) => setContrasena(event.target.value)}
          />
        </div>
        <div className="form-group">
          <label htmlFor="confirmarContrasena">Confirmar contraseña</label>
          <input
            type="password"
            id="confirmarContrasena"
            className="form-control mx-auto text-center w-50"
            value={confirmarContrasena}
            onChange={(event) => setConfirmarContrasena(event.target.value)}
          />
        </div>
        <br />
        <button className="btn boton mx-auto text-center w-50" type="submit">Registro</button>
      </form>
    );
  };

  // Html de la bienvenida para usuarios que han iniciado sesión
  const Bienvenida = ({ NombreUsuario }) => {
    return (
      <div className="container-fluid">
        <div className="row">
          <div className="col-md-6">
            <img
              src="https://via.placeholder.com/800x600"
              alt="Imagen de fondo de viajes"
              className="img-fluid"
            />
          </div>
          <div className="col-md-6">
            <div className="welcome-content">
              <h1>Bienvenido {NombreUsuario}</h1>
              <br /><hr className="Principal" /><br />
              <h2>¡Descubre nuevos destinos!</h2>
              <br />
              <p>
                ¡Explora nuevos destinos y reserva tus viajes con nosotros!
                Descubre lugares increíbles, alquila vehículos y vive experiencias
                inolvidables.
              </p>
              <br />
              <button className="btn boton mx-auto text-center w-50">
                Explorar Destinos
              </button>
              <br /><hr className="Principal" /><br />
              <h2>¿Necesitas ayuda?</h2>
              <br />
              <p>
                ¿Necesitas ayuda para planificar tu viaje? Nuestro equipo de
                expertos en viajes está aquí para ayudarte.
              </p>
              <a href="/" className="btn boton-sm">
                Contactar con nosotros
              </a>
            </div>
          </div>
        </div>
      </div>
    );
  };

  // Contenido principal de la aplicación
  const ContenidoPrincipal = () => {
    let NombreUsuario = sessionStorage.getItem('user_name');
    // Si el usuario no ha iniciado sesión, se muestra el formulario de login y registro
    if (NombreUsuario == null) {
      return (<div className="row text-center p-4 mx-auto example-row">
        <div className="w-25 p-2 col">
          {Contenedor_Secundario(<Login />, true)}
        </div>
        <div className="w-25 p-2 col">
          {Contenedor_Secundario(<Registro />, true)}
        </div>
      </div>);
    }
    // Si el usuario ha iniciado sesión, se muestra un mensaje de bienvenida
    return (
      <div className="row text-center p-4 mx-auto example-row">
        <div className="w-25 p-2 col">
          {Contenedor_Secundario(<Bienvenida NombreUsuario={NombreUsuario} />, true)}
        </div>
      </div>
    );
  };

  return (
    <div className="App example-row">
      {Contenedor_Principal(<ContenidoPrincipal />, false)}
    </div>
  );
}

export default App;
