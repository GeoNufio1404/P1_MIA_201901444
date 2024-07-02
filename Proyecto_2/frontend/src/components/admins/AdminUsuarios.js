import "../../index.css"
import { Contenedor_Principal, Contenedor_Secundario, Separacion, Division4_8 } from '../shared/Funciones';

function AdminUsuarios() {
  const FormularioUsuarios = () => {
    return (
      <form>
        <h2 className="text-center">Agregar Usuario</h2>
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
                <label>Correo</label>
                <input type="email" className="form-control" placeholder="Ingrese su correo electrónico" />
              </div>
            </div>
          </div>
          <div className="row">
            <div className="col-md-6">
              <div className="form-group">
                <label>Contraseña</label>
                <input type="password" className="form-control" placeholder="Ingrese su contraseña" />
              </div>
            </div>
            <div className="col-md-6">
              <div className="form-group">
                <label>Confirmar Contraseña</label>
                <input type="password" className="form-control" placeholder="Confirme su contraseña" />
              </div>
            </div>
          </div>
          <div className="form-group">
            <label>Tipo de usuario</label>
            <select className="form-control">
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