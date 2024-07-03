import "../../index.css";

// Items para administradores
const Items_Admin = [
  {
    text: "Administracion Usuarios",
    key: "AdminUsuarios",
  }
];

// Items para recepcionistas
const Items_Recep = [
  {
    text: "Solicitudes Viajes",
    key: "SolicitudesViajes",
  },
  {
    text: "Solicitudes Autos",
    key: "SolicitudesAutos",
  }
];

// Items para usuarios normales
const Items_Usuario = [
  {
    text: "Viajes",
    key: "Viajes",
  },
  {
    text: "Renta de Autos",
    key: "RentaAutos",
  }
];

// Funcion para mostrar items en el Navbar
function MostrarItems({ items, emptyItem }) {
  if (items.legth === 0) {
    return (<li className="nav-item"> {emptyItem} </li>);
  } else {
    return items.map((item) => {
      return (
        <li key={item.key} className="nav-item">
          <button className="btn Enfasis" onClick={() => window.open("/" + item.key, "_self")}> ╭╮{item.text}╭╮ </button>
        </li>
      );
    });
  };
};

// Funcion para devolver items dependiendo del tipo de usuario
function ComprobarTipoUsuario() {
  let tipoUsuario = sessionStorage.getItem("user_type");
  if (tipoUsuario === "Admin") {
    return Items_Admin;
  } else if (tipoUsuario === "Recep") {
    return Items_Recep;
  } else if (tipoUsuario === "User") {
    return Items_Usuario;
  } else {
    return [];
  }
};

// Boton para cerrar sesion
const BotonCerrarSesion = () => {

  function handleCerrarSesion() {
    sessionStorage.removeItem("user_name");
    sessionStorage.removeItem("user_type");
    window.open('/', '_self')
  };

  if (sessionStorage.getItem("user_name") === null) {
    return (<div></div>);
  }
  return (
    <button className="navbar-brand btn Enfasis" onClick={handleCerrarSesion}>╭╮Cerrar Sesion╭╮</button>
  );
};

function Navbar() {
  return (
    <div className="Navbar">
      <header>
        <nav className="navbar navbar-expand-lg navbar-dark Enfasis">
          <div className="container p-2">

            <button className="navbar-brand btn Enfasis" onClick={() => window.open('/', '_self')}>╭━╮ AviCar ╭━╮</button>

            <div className="collapse navbar-collapse" id="navbarSupportedContent">
              <ul className="navbar-nav mr-auto">
                <MostrarItems items={ComprobarTipoUsuario()} emptyItem="" />
              </ul>
            </div>

            <BotonCerrarSesion />
          </div>
        </nav>
      </header>
    </div>
  );
}

export default Navbar;
