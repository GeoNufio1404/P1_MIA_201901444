import '../index.css';
import React, { useEffect, useState } from 'react';

function TablaSimbolos() {
  const [simbolos, setSimbolos] = useState([]);

  useEffect(() => {
    fetch('http://localhost:5000/Simbolos')
      .then(response => response.json())
      .then(data => {
        setSimbolos(data.Simbolos);
      })
      .catch(error => console.error(error));
  }, []);

  return (
    <div className="TablaSimbolos">
      <div className="container Principal sombra w-50 p-1">
        <div className="col text-center mx-auto">
          <br />
          <h1 id="Titulo">Tabla Simbolos</h1>
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
                <th>Identificador</th>
                <th>Tipo Variable</th>
                <th>Tipo Dato</th>
                <th>Estructura</th>
                <th>Valor</th>
                <th>Entorno</th>
              </tr>
            </thead>
            <tbody className='Fondo'>
              {simbolos.map((simbolo, index) => (
                <tr key={index}>
                  <td>{simbolo.Identificador}</td>
                  <td>{simbolo.TipoVariable}</td>
                  <td>{simbolo.TipoDato}</td>
                  <td>{simbolo.Estructura}</td>
                  <td>{simbolo.Valor}</td>
                  <td>{simbolo.Entorno}</td>
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

export default TablaSimbolos;