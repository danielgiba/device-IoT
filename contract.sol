// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract TemperatureHumidityRegistry {
    struct SensorData {
        uint256 timestamp;
        string deviceId;
        uint256 temperature;
        uint256 humidity;
    }

    event DataRecorded(address indexed from, string deviceId, uint256 temperature, uint256 humidity);

    mapping(string => SensorData[]) private sensorDataMap;

    function recordData(string memory deviceId, uint256 temperature, uint256 humidity) public {
        SensorData memory newEntry = SensorData(block.timestamp, deviceId, temperature, humidity);
        sensorDataMap[deviceId].push(newEntry);
        emit DataRecorded(msg.sender, deviceId, temperature, humidity);
    }

    function getLastData(string memory deviceId) public view returns (uint256 timestamp, uint256 temperature, uint256 humidity) {
        uint256 length = sensorDataMap[deviceId].length;
        if (length > 0) {
            SensorData memory lastEntry = sensorDataMap[deviceId][length - 1];
            return (lastEntry.timestamp, lastEntry.temperature, lastEntry.humidity);
        } else {
            return (0, 0, 0);
        }
    }
}
