import React, { useState, useEffect } from 'react';

function TablaTokens() {
    const [tokens, setTokens] = useState([]);

    useEffect(() => {
        fetch('http://localhost:5000/Tokens')
            .then(response => response.json())
            .then(data => {
                setTokens(data.Tokens);
            })
            .catch(error => console.error(error));
    }, []);

    return (
        <div className="TablaTokens">
            <div className="container Principal sombra w-50 p-1">
                <div className="col text-center mx-auto">
                    <br />
                    <h1 id="Titulo">Tabla de Tokens</h1>
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
                                <th>Tipo Token</th>
                                <th>Lexema</th>
                                <th>Linea</th>
                                <th>Columna</th>
                            </tr>
                        </thead>
                        <tbody className='Fondo'>
                            {tokens.map((token, index) => (
                                <tr key={index}>
                                    <td>{token.Tipo}</td>
                                    <td>{token.Lexema}</td>
                                    <td>{token.Fila}</td>
                                    <td>{token.Columna}</td>
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

export default TablaTokens;