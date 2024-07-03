import "../../index.css"
import { Contenedor_Principal, Contenedor_Secundario, Separacion, Division4_8 } from '../shared/Funciones';
import { API } from "../../Globales";
import { useState, useRef } from 'react';

function AdminUsuarios() {
  const FormularioUsuarios = () => {
    const [Nombre, setNombreCompleto] = useState('');
    const [Username, setUsername] = useState('');
    const [Tipo, setTipo] = useState('User');
    const [Correo, setCorreoElectronico] = useState('');
    const [Password, setContrasena] = useState('');
    const [confirmarContrasena, setConfirmarContrasena] = useState('');

    const passwordRef = useRef(null);
    const confirmarPasswordRef = useRef(null);
    const correoRef = useRef(null);
    const usernameRef = useRef(null);
    const nombreRef = useRef(null);
    const tipoRef = useRef(null);

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
        "Password": Password,
        "TipoUsuario": Tipo
      };

      console.log(JSON.stringify(Datos));

      fetch(`${API}/admin/usuarios`, {
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
        } );
    };

    return (
      <form onSubmit={handleRegistro}>
        <h2 className="text-center">Agregar Usuario</h2>
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
                  placeholder="Ingrese su nombre completo"
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
          <div className="form-group">
            <label>Tipo de usuario</label>
            <select className="form-control" onChange={(event) => setTipo(event.target.value)} ref={tipoRef}>
              <option value="User">User</option>
              <option value="Admin">Admin</option>
              <option value="Recep">Recep</option>
            </select>
          </div>
          <br />
          <button type="submit" className="btn btn-block Enfasis2">
            Agregar usuario
          </button>
        </div>
      </form>
    );
  };

  const TablaUsuarios = () => {
    return (
      <table className="table table-striped sombra">
        <thead className="Enfasis2">
          <tr>
            <th>Nombre</th>
            <th>Correo</th>
            <th>Tipo de usuario</th>
            <th>Acciones</th>
          </tr>
        </thead>
        <tbody>
          {/* Aquí puedes renderizar la lista de usuarios */}
          <tr>
            <td>Nombre 1</td>
            <td>correo1@example.com</td>
            <td>User</td>
            <td>
              <button className="btn boton Boton_Editar">Editar</button>
              <button className="btn boton Enfasis2">Eliminar</button>
            </td>
          </tr>
          <tr>
            <td>Nombre 1</td>
            <td>correo1@example.com</td>
            <td>User</td>
            <td>
              <button className="btn Boton_Editar">Editar</button>
              <button className="btn boton Enfasis2">Eliminar</button>
            </td>
          </tr>
          <tr>
            <td>Nombre 1</td>
            <td>correo1@example.com</td>
            <td>User</td>
            <td>
              <button className="btn Boton_Editar">Editar</button>
              <button className="btn boton Enfasis2">Eliminar</button>
            </td>
          </tr>
          {/*... */}
        </tbody>
      </table>
    );
  };

  return (
    <div className="AdminUsuarios">
      {Contenedor_Principal("Administracion - Usuarios", Division4_8(Contenedor_Secundario(<FormularioUsuarios />, true), <TablaUsuarios />))}
    </div>
  );
}

export default AdminUsuarios;