import './Thermostat.css';
import axios from "axios";
import React, { useState, useEffect } from "react";


export default function Thermostat() {

    const [temp, setTemp] = useState();

    useEffect(() => {
      axios.get('http://localhost:8080/temp').then(
        response => {
          setTemp(response.data);
        }
      ).catch(error => {
        console.error(error);
      })
    }, [])

    return (
        <div className="thermostat-container">
            <svg width="400" height="400" viewBox="0 0 250 250" className="circular-progress">
                <circle className="bg"></circle>
                <circle className="fg"></circle>
                <circle className="middle"></circle>
                <text
                    x="50%"
                    y="50%"
                    textAnchor="middle"
                    className="progress-text">
                        {temp}
                </text>
            </svg>
        </div>
    );
}