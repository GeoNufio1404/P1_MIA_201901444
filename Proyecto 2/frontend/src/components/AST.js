import '../index.css';
import React, { useEffect, useState } from 'react';

function AST() {

  const [SVG, setSVG] = useState("");

  useEffect(() => {

    fetch('http://localhost:4000/Api/AST')
      .then((response) => response.json())
      .then((data) => {
        if (data.Status === 'ok') {
          setSVG(data.AST);
        }
      })
      .catch((error) => {
        console.error('Error al obtener el SVG:', error);
      });
  }, []);

  return (
    <div className="AST">
      <div className="container Principal sombra w-50 p-1">
        <div className="col text-center mx-auto">
          <br />
          <h1 id="Titulo">Reporte AST</h1>
          <br />
        </div>
      </div>
      <br />
      <div className="container-fixed mx-auto sombra text-center Principal">
        <br /><br />
        <div id="ContenedorAST" className="row text-center Fondo p-2 mx-auto sombra w-75">
          {SVG && (
            <iframe
              title="SVG Viewer"
              srcDoc={SVG}
              className="iframe-svg"
              width="100%" 
              style={{ minHeight: "700px" }} 
            />
          )}
        </div>
        <br />
        <hr className="Principal" />
        <br />
      </div>
      <br /><br />
    </div>
  );
}

export default AST;