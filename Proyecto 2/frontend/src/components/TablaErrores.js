import '../index.css';
import React, { useEffect, useState } from 'react';

function TablaErrores() {
  const [errores, setErrores] = useState([]);

  useEffect(() => {
    fetch('http://localhost:5000/Errores')
      .then(response => response.json())
      .then(data => {
        setErrores(data.Errores);
      })
      .catch(error => console.error(error));
  }, []);

  return (
    <div className="TablaErrores">
      <div className="container Principal sombra w-50 p-1">
        <div className="col text-center mx-auto">
          <br />
          <h1 id="Titulo">Tabla Errores</h1>
          <br />
        </div>
      </div>
      <br />
      <div className="container-fixed mx-auto sombra text-center Principal">
        <br /><br />
        <div className="row text-center p-2 w-75 mx-auto Fondo">
          <table className="table table-striped">
            <thead>
              <tr className='Enfasis'>
                <th>Tipo Error</th>
                <th>Lexema</th>
                <th>Descripcion</th>
                <th>Linea</th>
                <th>Columna</th>
              </tr>
            </thead>
            <tbody className='Fondo'>
              {errores.map((error, index) => (
                <tr key={index}>
                  <td>{error.TipoError}</td>
                  <td>{error.Lexema}</td>
                  <td>{error.Descripcion}</td>
                  <td>{error.Fila}</td>
                  <td>{error.Columna}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
        <br />
        <hr className="Principal" />
        <br />
      </div>
      <br /><br />
    </div>

  );
}

export default TablaErrores;