import "../../index.css"
import { Contenedor_Principal, Contenedor_Secundario, Separacion } from '../shared/Funciones';

function AdminUsuarios() {
  const FormularioUsuarios = () =>  {
    return (
      <form>
            <h2>Agregar nuevo usuario</h2>
            <Separacion />
            <div className="form-group">
              <label>Nombre</label>
              <input type="text" className="form-control" />
            </div>
            <div className="form-group">
              <label>Correo</label>
              <input type="email" className="form-control" />
            </div>
            <div className="form-group">
              <label>Contraseña</label>
              <input type="password" className="form-control" />
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
            <button type="submit" className="btn boton">
              Agregar usuario
            </button>
          </form>
    );
  };

  const TablaUsuarios = () => {
    return (
      <table className="table table-striped sombra">
        <thead className="Enfasis">
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
              <button className="btn Boton_Editar">Editar</button>
              <button className="btn boton">Eliminar</button>
            </td>
          </tr>
          <tr>
            <td>Nombre 1</td>
            <td>correo1@example.com</td>
            <td>User</td>
            <td>
              <button className="btn Boton_Editar">Editar</button>
              <button className="btn boton">Eliminar</button>
            </td>
          </tr><tr>
            <td>Nombre 1</td>
            <td>correo1@example.com</td>
            <td>User</td>
            <td>
              <button className="btn Boton_Editar">Editar</button>
              <button className="btn boton">Eliminar</button>
            </td>
          </tr>
          {/*... */}
        </tbody>
      </table>
    );
  };

  const Division1_3 = (ComponeneteIzq, ComponeneteDer) => {
    return (
      <div className="container-fluid">
        <div className="row">
          <div className="col-4">
            {ComponeneteIzq}
          </div>
          <div className="col-8">
            {ComponeneteDer}
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="AdminUsuarios">
      <div className="container Principal sombra w-50 p-1">
        <div className="col text-center mx-auto">
          <br />
          <h1 id="Titulo">Administracion - Usuarios</h1>
          <br />
        </div>
      </div>
      <br />
      {Contenedor_Principal(Division1_3(Contenedor_Secundario(<FormularioUsuarios />, true), <TablaUsuarios />))}
    </div>
  );
}

export default AdminUsuarios;