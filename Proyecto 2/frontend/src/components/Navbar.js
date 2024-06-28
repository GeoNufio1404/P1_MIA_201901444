
import "../index.css";

function PaginaPrincipal() {
  window.open("/", "_self");
}

function PaginaAST() {
  window.open("/AST", "_self");
}

function PaginaTablaErrores() {
  window.open("/TablaErrores", "_self");
}

function PaginaTablaTokens() {
  window.open("/TablaTokens", "_self");
}

function PaginaTablaSimbolos() {
  window.open("/TablaSimbolos", "_self");
}

function Navbar() {
  return (
    <div className="Navbar">
      <header>
        <nav className="navbar navbar-expand-lg navbar-dark Enfasis">
          <div className="container p-2">

            <button className="navbar-brand btn Enfasis" onClick={PaginaPrincipal}> OLCScript</button>

            <div className="collapse navbar-collapse" id="navbarSupportedContent">
              <ul className="navbar-nav mr-auto">
                <li id="Item-Editor" className="nav-item">
                  <button className="Boton btn Enfasis" onClick={PaginaTablaErrores}>Tabla Errores</button>
                </li>
                <li id="Item-Reportes" className="nav-item">
                  <button className="Boton btn Enfasis" onClick={PaginaTablaTokens}>Tabla Tokens</button>
                </li>
                <li id="Item-Reportes" className="nav-item">
                  <button className="Boton btn Enfasis" onClick={PaginaTablaSimbolos}>Tabla Simbolos</button>
                </li>
                <li id="Item-Reportes" className="nav-item">
                  <button className="Boton btn Enfasis" onClick={PaginaAST}>AST</button>
                </li>
              </ul>
            </div>
          </div>
        </nav>
      </header>
    </div>
  );
}

export default Navbar;
