import React, { useState, useRef } from 'react';
import './index.css';

function App() {

  const [entrada, setEntrada] = useState('');
  const [numeros, setNumeros] = useState('');
  const [salida, setSalida] = useState('');
  const entradaRef = useRef(null);
  const numerosRef = useRef(null);

  function EjecutarCodigo() {
    const url = 'http://localhost:5000/Analizar';
    const data = entrada;
    fetch(url, {
      method: 'POST',
      body: data,
      headers: {
        'Content-Type': 'text/plain'
      }
    })
      .then(response => response.json())
      .then(data => {
        setSalida(data.Salida);
      })
      .catch(error => console.error(error));
  }

  function Guardar() {
    const texto = entrada;
    const nombre = prompt('Ingrese el nombre del archivo a guardar', 'NuevoArchivo');

    if (nombre) {
      const a = document.createElement('a');
      a.href = 'data:text/plain;charset=utf-8,' + encodeURIComponent(texto);
      a.download = nombre + '.olc';
      a.click();
    }
  }


  function handleEntradaChange(event) {
    const texto = event.target.value;
    const lineas = texto.split('\n').length;
    setEntrada(texto);
    setNumeros([...Array(lineas).keys()].map(i => i + 1).join('\n'));
  }

  function handleCargarArchivos(event) {
    const archivo = event.target.files[0];
    const lector = new FileReader();
    lector.onload = function (evento) {
      const contenido = evento.target.result;
      setEntrada(contenido);
      const lineas = contenido.split('\n').length;
      setNumeros([...Array(lineas).keys()].map(i => i + 1).join('\n'));
    };
    lector.readAsText(archivo);
  }

  function handleTabKey(event) {
    if (event.key === 'Tab') {
      event.preventDefault();
      const { selectionStart } = event.target;
      const newEntrada = entrada.slice(0, selectionStart) + '\t' + entrada.slice(selectionStart);
      setEntrada(newEntrada);
    }
  }

  function handleEntradaScroll(event) {
    const scrollTop = event.target.scrollTop;
    numerosRef.current.scrollTop = scrollTop;
  }

  return (
    <div className="App example-row">
      <div className="container Principal sombra w-50 p-1">
        <div className="col text-center mx-auto">
          <br />
          <h1 id="Titulo">Menu Principal</h1>
          <br />
        </div>
      </div>
      <br />
      <div className="container-fixed mx-auto sombra text-center Principal example-row">
        <br /><br />
        <div className="row text-center p-2 mx-auto example-row">


          <div className="w-25 p-2 example-content-secondary">
            <div className="Fondo p-2">
              <br />
              <hr className="Principal" />
              <br />
              <h3 id="Bienvenida-Editor">Bienvenido!</h3>
              <br />
              <hr className="Principal" />
              <br />
              <div className="btn-group-vertical mx-auto text-center w-75">
                <br />
                <button className="btn boton mx-auto text-center w-75" onClick={() => EjecutarCodigo()}>Ejecutar Codigo</button>
                <br />
                <button className="btn boton mx-auto text-center w-75" onClick={() => Guardar()}>Descargar Archivo</button>
                <br />
              </div>
              <br />
              <hr className="Principal" />
              <br />
              <label htmlFor="Editor-CargadorArchivos mx-auto text-center w-75">Cargar Archivo</label>
              <br />
              <input
                className="mx-auto text-center w-75" type="file" id="Editor-CargadorArchivos" accept=".olc, .txt" onChange={(event) => handleCargarArchivos(event)}
              />
              <br />
              <hr className="Principal" />
              <br />
            </div>
          </div>


          <div className="example-content-main w-75 p-2">
            <div className="Fondo p-2">
              <br />
              <hr className="Principal" />
              <br />
              <div className="row text-center mx-auto">
                <div className="col">
                  <form>
                    <label htmlFor="Editor-LabelEntrada">Entrada</label>
                    <br />
                    <div className="editor sombra">
                      <textarea
                        id="Entrada-Numeros"
                        className="TextArea"
                        rows="20"
                        cols="4"
                        onChange={(event) => handleEntradaChange(event)}
                        value={numeros}
                        readOnly
                        style={{ overflow: 'static' }}
                        ref={numerosRef}
                      ></textarea>
                      <textarea
                        id="Entrada-Default"
                        className="TextArea w-100"
                        rows="20"
                        cols="70"
                        onChange={(event) => handleEntradaChange(event)}
                        onKeyDown={(event) => handleTabKey(event)}
                        onScroll={(event) => handleEntradaScroll(event)}
                        value={entrada}
                        style={{ overflow: 'auto' }}
                        ref={entradaRef}
                      ></textarea>
                    </div>
                  </form>
                </div>
                <div className="col">
                  <form>
                    <label htmlFor="Editor-LabelSalida">Salida</label>
                    <br />
                    <div className="editor sombra">
                      <textarea
                        id="Salida-Default"
                        className="TextArea w-100"
                        rows="20"
                        cols="70"
                        value={salida}
                        readOnly
                        style={{ overflow: 'auto' }}
                      ></textarea>
                    </div>
                  </form>
                </div>
              </div>
              <br />
              <hr className="Principal" />
              <br />
            </div>
          </div>
          <br /><br />
        </div>
      </div>
    </div>
  );
}

export default App;