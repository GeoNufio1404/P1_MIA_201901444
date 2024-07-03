import './index.css';
import React, { useState, useRef } from 'react';
import { Contenedor_Principal, Contenedor_Secundario, Separacion, Division4_8, Contenedor_Titulo } from './components/shared/Funciones';
import { API } from "./Globales";

function App() {

  // Html del login
  const Login = () => {
    const [Usuario, setUsername] = useState('');
    const [Password, setPassword] = useState('');

    const usernameRef = useRef(null);
    const passwordRef = useRef(null);

    function handleLogin(event) {
      event.preventDefault();

      // Hacer la peticion al backend para verificar si el usuario existe
      fetch(`${API}/usuario/login`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({ Usuario, Password })
      })
        .then(response => response.json())
        .then(res => {
          // Handle the response from the backend
          console.log(res);

          if (res.status === false) {
            alert('Usuario o contraseña incorrectos');
            return;
          }

          // Add login logic here
          sessionStorage.setItem('user_name', Usuario);
          sessionStorage.setItem('user_type', res.data);

          // Alerta de que el usuario ha iniciado sesión
          alert('Usuario ha iniciado sesión correctamente');

          window.location.reload();
        });
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
            value={Usuario}
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
            value={Password}
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

    const [Nombre, setNombreCompleto] = useState('');
    const [Username, setUsername] = useState('');
    const [fotoPerfil, setFotoPerfil] = useState('https://via.placeholder.com/150');
    const [Correo, setCorreoElectronico] = useState('');
    const [Password, setContrasena] = useState('');
    const [confirmarContrasena, setConfirmarContrasena] = useState('');

    const passwordRef = useRef(null);
    const confirmarPasswordRef = useRef(null);
    const correoRef = useRef(null);
    const usernameRef = useRef(null);
    const nombreRef = useRef(null);

    const handleRegistro = (event) => {
      event.preventDefault();

      if (Password !== confirmarContrasena) {
        alert('Las contraseñas no coinciden');
        return;
      }

      let Datos = {
        "Nombre": Nombre,
        "Usuario": Username,
        "Correo": Correo,
        "Password": Password
      };

      console.log(JSON.stringify(Datos));

      fetch(`${API}/usuario/registro`, {
        method: 'POST',
        body: JSON.stringify(Datos),
      })
        .then(response => response.json())
        .then(res => {
          // Handle the response from the backend
          console.log(res);

          if (res.status === false) {
            alert('Error al registrar usuario');
            return;
          } else {
            alert('Usuario registrado correctamente');
            window.location.reload();
          }
        }
        );
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
                <input type="text"
                  className="form-control"
                  value={Nombre}
                  onChange={(event) => setNombreCompleto(event.target.value)}
                  ref={nombreRef}
                  placeholder="Ingrese su nombre completo" />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Username</label>
                <input type="text"
                  className="form-control"
                  value={Username}
                  onChange={(event) => setUsername(event.target.value)}
                  ref={usernameRef}
                  placeholder="Ingrese su nombre de Usuario"
                />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Contraseña</label>
                <input type="password"
                  className="form-control"
                  value={Password}
                  onChange={(event) => setContrasena(event.target.value)}
                  ref={passwordRef}
                  placeholder="Ingrese su contraseña"
                />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Correo</label>
                <input type="email"
                  className="form-control"
                  value={Correo}
                  onChange={(event) => setCorreoElectronico(event.target.value)}
                  ref={correoRef}
                  placeholder="Ingrese su correo electrónico"
                />
              </div>
            </div>

            <div className="col-md-6">
              <div className="form-group">
                <label>Confirmar Contraseña</label>
                <input type="password"
                  className="form-control"
                  value={confirmarContrasena}
                  onChange={(event) => setConfirmarContrasena(event.target.value)}
                  ref={confirmarPasswordRef}
                  placeholder="Confirme su contraseña"
                />
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
              {Contenedor_Titulo('Bienvenido a AviCar ' + NombreUsuario)}
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
