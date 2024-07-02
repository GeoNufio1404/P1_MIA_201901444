import './index.css';
import React, { useState, useRef } from 'react';
import { Contenedor_Principal, Contenedor_Secundario, Separacion, Division4_8 } from './components/shared/Funciones';

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
        <h2 className="text-center">Iniciar Sesion</h2>
        <Separacion />
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
        <button className="btn boton mx-auto text-center w-50 Enfasis2" onClick={(event) => handleLogin(event)}>Login</button>
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
        <h2 className="text-center">Registrarse</h2>
        <Separacion />
        <div className="container">
          <div className="row">

            <div className="col-md-6">
              <div className="form-group">
                <label>Nombre Completo</label>
                <input type="text" className="form-control" placeholder="Ingrese su nombre completo" />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Username</label>
                <input type="text" className="form-control" placeholder="Ingrese su nombre de Usuario" />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Contraseña</label>
                <input type="password" className="form-control" placeholder="Ingrese su contraseña" />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Correo</label>
                <input type="email" className="form-control" placeholder="Ingrese su correo electrónico" />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Confirmar Contraseña</label>
                <input type="password" className="form-control" placeholder="Confirme su contraseña" />
              </div>
            </div>
          </div>
          <Separacion />

          <div className="form-group text-center">
            <label htmlFor="fotoPerfil">Foto de perfil</label>
            <br />
            <img src={fotoPerfil} alt="Foto de perfil" />
            <br /><br />
            <input
              type="file"
              id="fotoPerfil"
              className="Secundario"
              onChange={(event) => setFotoPerfil(event.target.files[0])}
            />
          </div>
          <Separacion />
          <button type="submit" className="btn btn-block Enfasis2">
            Agregar usuario
          </button>
        </div>
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
            <h2 className="text-center">Bienvenido {NombreUsuario}!</h2>
              <Separacion />
              <h2>¡Descubre nuevos destinos!</h2>
              <br />
              <p>
                ¡Explora nuevos destinos y reserva tus viajes con nosotros!
                Descubre lugares increíbles, alquila vehículos y vive experiencias
                inolvidables.
              </p>
              <br />
              <button className="btn boton mx-auto text-center w-50 Enfasis2">
                Explorar Destinos
              </button>
              <Separacion />
              <h2>¿Necesitas ayuda?</h2>
              <br />
              <p>
                ¿Necesitas ayuda para planificar tu viaje? Nuestro equipo de
                expertos en viajes está aquí para ayudarte.
              </p>
              <a href="/" className="btn Boton_Editar">
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
      return (Division4_8(Contenedor_Secundario(<Login />, true), Contenedor_Secundario(<Registro />, false)));
    }
    // Si el usuario ha iniciado sesión, se muestra un mensaje de bienvenida
    return (
      Contenedor_Secundario(<Bienvenida NombreUsuario={NombreUsuario} />, true)
    );
  };

  return (
    <div className="App">
      {Contenedor_Principal(null, <ContenidoPrincipal />)}
    </div>
  );
}

export default App;
